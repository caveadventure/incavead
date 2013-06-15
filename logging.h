#ifndef __LOGGING_H
#define __LOGGING_H

#include <iostream>
#include <fstream>

namespace logger {

struct Sink {
    std::ofstream out;

    Sink(const std::string& name) {

	out.exceptions(std::ofstream::failbit|std::ofstream::badbit);
	out.open(name, std::ios::out|std::ios::app);
    }

    ~Sink() { out.close(); }

    template <typename T>
    Sink& operator<<(const T& t) {
        out << t;
        return (*this);
    }
};

}

#endif
