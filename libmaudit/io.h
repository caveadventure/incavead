#ifndef __MAUDIT_IO_H
#define __MAUDIT_IO_H

#include <stdio.h>

#include <string>

namespace maudit {

struct stdin_stdout {

    stdin_stdout() {
        ::setvbuf(stdout, NULL, _IONBF, 0);
    }

    bool write(const std::string& s) {
        size_t n = ::fwrite(s.data(), s.size(), 1, stdout);
        if (n != 1) {
            return false;
        }

        return true;
    }

    bool read(unsigned char& c) {
        size_t n = ::fread((void*)(&c), 1, 1, stdin);
        if (n != 1) {
            return false;
        }

        return true;
    }
};

}

#endif
