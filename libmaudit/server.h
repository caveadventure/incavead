#ifndef __MAUDIT_SERVER_H
#define __MAUDIT_SERVER_H

#include <stdexcept>

#include <string>
#include <vector>

#include <string.h>
#include <unistd.h>

#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>


namespace maudit {


struct client_socket {

private:

    static const size_t buffsize = 1<<16;

    typedef std::vector<unsigned char> buff_t;
    buff_t buff;
    buff_t::const_iterator buffi;
    buff_t::const_iterator buffe;

public:

    int fd;

    ~client_socket() {
        if (fd >= 0) {
            ::shutdown(fd, SHUT_RDWR);
            ::close(fd);
        }
    }

    client_socket(int _fd) : fd(_fd) {

        buff.resize(buffsize);
        buffi = buff.end();
        buffe = buff.end();
    }

    bool write(const std::string& s) {

        ssize_t tmp = ::send(fd, s.data(), s.size(), MSG_NOSIGNAL);

        if (tmp < 0 || tmp != (ssize_t)s.size()) {
            return false;
        }

        return true;
    }

    bool read(unsigned char& c) {

        if (buffi == buffe) {

            ssize_t tmp = 0;
            tmp = ::recv(fd, &(buff[0]), buffsize, 0);

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
};


struct server_socket {

private:

    void teardown(const std::string& msg) {

        ::shutdown(fd, SHUT_RDWR);
        ::close(fd);
        fd = -1;

        throw std::runtime_error(msg);
    }

public:

    int fd;

    ~server_socket() {
        if (fd >= 0) {
            ::shutdown(fd, SHUT_RDWR);
            ::close(fd);
        }
    }
        
    server_socket(const std::string& host, unsigned int port) : fd(-1) {

        fd = ::socket(AF_INET, SOCK_STREAM, 0);

        if (fd < 0) {
            throw std::runtime_error("could not socket()");
        }

        int is_true = 1;
        if (::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &is_true, sizeof(is_true)) < 0)
            teardown("could not setsockopt(SO_REUSEADDR) : ");

        if (::setsockopt(fd, SOL_TCP, TCP_NODELAY, &is_true, sizeof(is_true)) < 0)
            teardown("could not setsockopt(TCP_NODELAY) : ");

        struct sockaddr_in addr;
        ::memset(&addr, 0, sizeof(addr));

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        if (::inet_pton(AF_INET, host.c_str(), (void*)&addr.sin_addr) <= 0)
            teardown("could not inet_pton() : ");

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

