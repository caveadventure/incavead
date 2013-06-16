#ifndef __LOGGING_H
#define __LOGGING_H

#include <iostream>
#include <fstream>

namespace logger {

struct Sink {
    std::string filename;
    std::string msg;

    Sink(const std::string& name) : filename(name) {}

    ~Sink() {
        try {
            std::ofstream out;
            out.exceptions(std::ofstream::failbit|std::ofstream::badbit);
            out.open(filename, std::ios::out|std::ios::app);
            out << msg;
            out.close();
        } catch(...) {
        }
    }

    void operator<<(const std::string& t) {
        msg += t;
    }
};

}

#endif
