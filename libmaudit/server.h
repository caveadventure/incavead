#ifndef __MAUDIT_SERVER_H
#define __MAUDIT_SERVER_H

#include <stdexcept>

#include <string>
#include <vector>

#include <string.h>
#include <unistd.h>

#include "network.h"

#include "lz77.h"


namespace maudit {


struct client_socket {

private:

    static const size_t buffsize = 1<<16;

    typedef std::vector<unsigned char> buff_t;
    buff_t buff;
    buff_t::const_iterator buffi;
    buff_t::const_iterator buffe;

    lz77::compress_t compressor;
    bool compression;

public:

    int fd;

    ~client_socket() {
        if (fd >= 0) {
            ::shutdown(fd, SHUT_RDWR);
            ::CLOSE(fd);
        }
    }

    client_socket(int _fd) : compressor(8, 4096), compression(false), fd(_fd) {

        buff.resize(buffsize);
        buffi = buff.end();
        buffe = buff.end();
    }

    void set_compression(bool c) {
        compression = c;
    }

    bool write_(const std::string& s) {

        ssize_t tmp = ::send(fd, s.data(), s.size(), MSG_NOSIGNAL);

        if (tmp < 0 || tmp != (ssize_t)s.size()) {
            return false;
        }

        return true;
    }

    bool write(const std::string& s) {

        if (compression) {
            std::string data = compressor.feed(s);

            return write_(data);

        } else {
            return write_(s);
        }
    }

    bool read(unsigned char& c) {

        if (buffi == buffe) {

            ssize_t tmp = 0;
            tmp = ::recv(fd, RECV_TYPE_CAST &(buff[0]), buffsize, 0);

            if (tmp < 0) {
                return false;
            }

            if (tmp == 0) {
                return false;
            }

            buffi = buff.begin();
            buffe = buff.begin() + tmp;
        }

        c = *buffi;
        ++buffi;

        return true;
    }

    unsigned int peer_ip() {

        struct sockaddr_in address;
        SOCKLEN_T address_len = sizeof(address);
        int r = ::getpeername(fd, (struct sockaddr*)&address, &address_len);

        if (r == 0) {
            return address.sin_addr.s_addr;
        }

        return 0;
    }
};


struct server_socket {

private:

    void teardown(const std::string& msg) {

        ::shutdown(fd, SHUT_RDWR);
        ::CLOSE(fd);
        fd = -1;

        throw std::runtime_error(msg);
    }

public:

    int fd;

    ~server_socket() {
        if (fd >= 0) {
            ::shutdown(fd, SHUT_RDWR);
            ::CLOSE(fd);
        }

        NETWORK_STOP();
    }
        
    server_socket(unsigned int port) : fd(-1) {

        NETWORK_INIT();

        fd = ::socket(AF_INET, SOCK_STREAM, 0);

        if (fd < 0) {
            throw std::runtime_error("could not socket()");
        }

        int is_true = 1;
        if (::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, SETSOCKOPT_TYPE_CAST &is_true, sizeof(is_true)) < 0)
            teardown("could not setsockopt(SO_REUSEADDR) : ");

        if (::setsockopt(fd, SOL_TCP, TCP_NODELAY, SETSOCKOPT_TYPE_CAST &is_true, sizeof(is_true)) < 0)
            teardown("could not setsockopt(TCP_NODELAY) : ");

        struct sockaddr_in addr;
        ::memset(&addr, 0, sizeof(addr));

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        addr.sin_addr.s_addr = 0;

        //if (::inet_pton(AF_INET, host.c_str(), (void*)&addr.sin_addr) <= 0)
        //    teardown("could not inet_pton() : ");

        if (::bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
            teardown("could not bind() : ");

        if (::listen(fd, 1024) < 0)
            teardown("could not listen() : ");
    }

    int accept() {

        int client = ::accept(fd, NULL, NULL);

        if (client < 0) {
            throw std::runtime_error("could not accept()");
        }

        return client;
    }
};


}

#endif

