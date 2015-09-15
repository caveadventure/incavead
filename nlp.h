#ifndef __NLP_H
#define __NLP_H

#include "rcode.h"
#include "strings_bank.h"

namespace nlp {

struct parsed_name {

    enum cmd_t {
        CHARS,
        WHEN_ONE,
        WHEN_MANY,
        NUMBER,
        NUMBER_WHEN_MANY,
        RCODE
    };

    std::vector< std::pair<cmd_t, std::string> > pattern;
        
    parsed_name(const std::string& name) {

        enum {
            TEXT,
            PCT,
            ONE,
            MANY
        } state = TEXT;

        for (unsigned char c : name) {

            switch (state) {

            case TEXT:
                if (c == '%') {

                    state = PCT;
                
                } else {

                    if (pattern.empty() || pattern.back().first != CHARS) {
                        pattern.push_back(std::make_pair(CHARS, ""));
                    }

                    pattern.back().second += c;
                }
                break;

            case PCT:
                if (c == '{') {
                    state = ONE;

                } else if (c == '(') {
                    state = MANY;

                } else if (c == '#') {
                    state = TEXT;
                    pattern.push_back(std::make_pair(NUMBER, ""));

                } else if (c == '*') {
                    state = TEXT;
                    pattern.push_back(std::make_pair(RCODE, ""));

                } else {
                    state = TEXT;

                    if (pattern.empty() || pattern.back().first != CHARS) {
                        pattern.push_back(std::make_pair(CHARS, ""));
                    }

                    pattern.back().second += c;
                }
                break;

            case ONE:
                if (c == '}') {
                    state = TEXT;

                } else {

                    if (pattern.empty() || pattern.back().first != WHEN_ONE) {
                        pattern.push_back(std::make_pair(WHEN_ONE, ""));
                    }

                    pattern.back().second += c;
                }
                break;

            case MANY:
                if (c == ')') {
                    state = TEXT;

                } else if (c == '#') {
                    pattern.push_back(std::make_pair(NUMBER_WHEN_MANY, ""));

                } else {

                    if (pattern.empty() || pattern.back().first != WHEN_MANY) {
                        pattern.push_back(std::make_pair(WHEN_MANY, ""));
                    }

                    pattern.back().second += c;
                }
                break;
            }
        }
    }

    std::string make(size_t n, bool capitals) {

        std::string ret;

        for (const auto& i : pattern) {

            switch (i.first) {

            case CHARS:
                ret += i.second;
                break;

            case NUMBER:
            {
                char tmp[256];
                ::snprintf(tmp, 255, "%zu", n);
                ret += tmp;
                break;
            }

            case NUMBER_WHEN_MANY:
                if (n > 1) {
                    char tmp[256];
                    ::snprintf(tmp, 255, "%zu", n);
                    ret += tmp;
                }
                break;

            case WHEN_ONE:
                if (n == 1) {
                    ret += i.second;
                }
                break;

            case WHEN_MANY:
                if (n > 1) {
                    ret += i.second;
                }
                break;

            case RCODE:
                ret += rcode::magick_encode(n);
                break;
            }
        }

        if (capitals && ret.size() > 0) {
            ret[0] = ::toupper(ret[0]);
        }

        return ret;
    }
};


struct _buffer {
    std::string::const_iterator ti;
    std::string::const_iterator te;
    std::string& out;

    bool is_start;

    enum {
        TEXT,
        PCT,
        PERIOD
    } state;

    _buffer(const std::string& tmpl, std::string& _out) :
        ti(tmpl.begin()), te(tmpl.end()), out(_out), is_start(true), state(TEXT)
        {}

    
    unsigned char consume() {
        while (ti != te) {

            unsigned char c = *(ti);
            ++ti;

            if (c == '%') {
                state = PCT;

            } else if (c == '.') {
                out += c;
                state = PERIOD;

            } else {

                switch (state) {
                case TEXT:
                    out += c;
                    is_start = false;
                    break;

                case PCT:
                    state = TEXT;
                    if (c == '%') {
                        out += c;
                    } else {
                        return c;
                    }
                    break;

                case PERIOD:
                    out += c;
                    if (::isspace(c)) {
                        is_start = true;
                    } else {
                        is_start = false;
                    }
                    break;
                }
            }
        }

        return '\0';
    }
};

struct count {};


void message(_buffer& b) {

    b.out.append(b.ti, b.te);
    return;
}

template <typename... TAIL>
void message(_buffer& b, const std::string& s, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 's') {
        b.out += s;

    } else if (c == 'S' && s.size() > 0) {
        b.out += ::toupper(s[0]);
        b.out += s.substr(1);
    }

    message(b, args...);
}

template <typename... TAIL>
void message(_buffer& b, unsigned int v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'd') {
        char tmp[256];
        ::snprintf(tmp, 255, "%zu", (size_t)v);
        b.out += tmp;
    }

    message(b, args...);
}

template <typename... TAIL>
void message(_buffer& b, unsigned long long v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'd') {
        char tmp[256];
        ::snprintf(tmp, 255, "%llu", v);
        b.out += tmp;
    }

    message(b, args...);
}

template <typename... TAIL>
void message(_buffer& b, unsigned long v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'd') {
        char tmp[256];
        ::snprintf(tmp, 255, "%lu", v);
        b.out += tmp;
    }

    message(b, args...);
}

template <typename... TAIL>
void message(_buffer& b, long long v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'd') {
        char tmp[256];
        ::snprintf(tmp, 255, "%lld", v);
        b.out += tmp;
    }

    message(b, args...);
}

template <typename... TAIL>
void message(_buffer& b, long v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'd') {
        char tmp[256];
        ::snprintf(tmp, 255, "%ld", v);
        b.out += tmp;
    }

    message(b, args...);
}

template <typename... TAIL>
void message(_buffer& b, int v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'd') {
        char tmp[256];
        ::snprintf(tmp, 255, "%zd", (ssize_t)v);
        b.out += tmp;
    }

    message(b, args...);
}

template <typename... TAIL>
void message(_buffer& b, double v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'd') {
        char tmp[256];
        ::snprintf(tmp, 255, "%g", v);
        b.out += tmp;

    } else if (c == 'f') {
        char tmp[256];
        ::snprintf(tmp, 255, "%.2f", v);
        b.out += tmp;
    }

    message(b, args...);
}

template <typename... TAIL>
void message(_buffer& b, float v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'd') {
        char tmp[256];
        ::snprintf(tmp, 255, "%g", v);
        b.out += tmp;

    } else if (c == 'f') {
        char tmp[256];
        ::snprintf(tmp, 255, "%.2f", v);
        b.out += tmp;
    }

    message(b, args...);
}

template <typename... TAIL>
void message(_buffer& b, char v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'c') {
        b.out += v;
    }

    message(b, args...);
}

template <typename T, typename... TAIL>
void message(_buffer& b, count, const T& val, unsigned int count, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 's' || c == 'S') {

        parsed_name pn(val.name);
        b.out += pn.make(count, (c == 'S' ? true : b.is_start));
    }

    message(b, args...);
}

template <typename T, typename... TAIL>
void message(_buffer& b, const T& val, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 's' || c == 'S') {
        parsed_name pn(val.name);
        b.out += pn.make(1, (c == 'S' ? true : b.is_start));
    }

    message(b, args...);
}

template <typename... ARGS>
std::string message(const std::string& tmpl, const ARGS&... args) {

    std::string ret;
    _buffer b(tmpl, ret);

    message(b, args...);

    return ret;
}

template <typename... ARGS>
std::string message(const std::pair<uint64_t, const char*>& tmpl, const ARGS&... args) {

    return message(strings().get(tmpl.first, tmpl.second), args...);
}

}

#endif
