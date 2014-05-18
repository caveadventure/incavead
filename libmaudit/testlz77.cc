
#include <stdlib.h>
#include <sys/time.h>
#include <string>
#include <iostream>

struct bm {
    struct timeval b;
    std::string msg;
    bm(const std::string& s) : msg(s) {
        gettimeofday(&b, NULL);
    }
    ~bm() {
        struct timeval e;
        gettimeofday(&e, NULL);
        size_t a = (e.tv_sec*1e6 + e.tv_usec);
        size_t q = (b.tv_sec*1e6 + b.tv_usec);
        std::cout << msg << ": " << ((double)a-(double)q)/1e6 << std::endl;
    }
};

struct bm_s {
    struct timeval b;
    double& _s;
    bm_s(double& s) : _s(s) {
        gettimeofday(&b, NULL);
    }
    ~bm_s() {
        struct timeval e;
        gettimeofday(&e, NULL);
        size_t a = (e.tv_sec*1e6 + e.tv_usec);
        size_t q = (b.tv_sec*1e6 + b.tv_usec);
        _s += ((double)a-(double)q)/1e6;
    }
};


#include "lz77.h"

#include <fstream>

int main(int argc, char** argv) {

    std::string inp(argv[3]);

    if (inp == "-f") {
        bm _x1("reading");

        std::ifstream in(argv[4], std::ios::in | std::ios::binary);

        if (!in)
            return 1;

        std::string data;
        in.seekg(0, std::ios::end);
        data.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&data[0], data.size());
        in.close();

        inp.swap(data);

    } else if (inp == "-d") {

        std::ifstream in(argv[4], std::ios::in | std::ios::binary);

        if (!in)
            return 1;

        std::string data;
        in.seekg(0, std::ios::end);
        data.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&data[0], data.size());
        in.close();

        inp.swap(data);

        lz77::decompress_t decompress;
        std::string extra;

        for (unsigned char cc : inp) { 
            decompress.feed(std::string(1, cc), extra);
        }

        std::ifstream in2(argv[5], std::ios::in | std::ios::binary);

        if (!in2)
            return 1;

        data.clear();
        in2.seekg(0, std::ios::end);
        data.resize(in2.tellg());
        in2.seekg(0, std::ios::beg);
        in2.read(&data[0], data.size());
        in2.close();

        inp.swap(data);

        for (unsigned char cc : inp) { 
            decompress.feed(std::string(1, cc), extra);
        }

        std::cout << std::string(decompress.outb, decompress.out) << std::endl;

        return 0;
    }

    size_t a = ::atoi(argv[1]);
    size_t b = ::atoi(argv[2]);

    std::string out;

    {
        bm _x2("compressing");
        out = lz77::compress(inp, a, b);
    }

    std::cout << "c." << out.size() << "  uc." << inp.size() << std::endl;

    lz77::decompress_t decompress;

    {
        bm _x2("decompressing");
        std::string extra;

        /*
        size_t nb = 0;
        size_t ne = std::max(out.size(), (size_t)256);
        bool done = decompress.start(std::string(out.begin() + nb, out.begin() + ne), extra);

        while (!done) {
            size_t tmp = ne;
            ne = std::max(out.size(), ne + 256);
            nb = tmp;
            done = decompress.more(std::string(out.begin() + nb, out.begin() + ne), extra);
        }
        */

        if (!decompress.feed(out, extra) || extra.size() > 0) {
            std::cout << "Sanity error: failed to decompress whole buffer." << std::endl;
            return 1;
        }
    }

    if (decompress.result() != inp) {
        std::cout << "Compression-decompression equivalence test failed!" << std::endl;

        if (decompress.result().size() < 1024)
            std::cout << "  " << decompress.result() << std::endl;

        return 1;
    }

    return 0;
}

