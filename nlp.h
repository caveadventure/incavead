#ifndef __NLP_H
#define __NLP_H

namespace nlp {

struct parsed_name {

    std::string base;
    std::vector< std::pair<size_t, std::string> > when_one;
    std::vector< std::pair<size_t, std::string> > when_many;

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
                    base += c;
                }
                break;

            case PCT:
                if (c == '{') {
                    state = ONE;
                    when_one.push_back(std::make_pair(base.size(), ""));

                } else if (c == '(') {
                    state = MANY;
                    when_many.push_back(std::make_pair(base.size(), ""));

                } else {
                    state = TEXT;
                    base += c;
                }
                break;

            case ONE:
                if (c == '}') {
                    state = TEXT;

                } else {
                    when_one.back().second += c;
                }
                break;

            case MANY:
                if (c == ')') {
                    state = TEXT;

                } else {
                    when_many.back().second += c;
                }
                break;
            }
        }
    }

    template <typename T>
    std::string make_(const T& when_) {
        std::string ret;

        auto woi = when_.begin();

        for (size_t i = 0; i <= base.size(); ++i) {

            if (woi != when_.end() && i == woi->first) {
                ret += woi->second;
                ++woi;
                --i;
                continue;
            }

            if (i < base.size()) {
                ret += base[i];
            }
        }

        return ret;
    }

    std::string make_one() {
        return make_(when_one);
    }

    std::string make_many() {
        return make_(when_many);
    }

    std::string make(size_t n, bool capitals) {

        std::string ret;

        if (n == 1) {
            ret = make_one();

        } else {

            char tmp[256];
            ::snprintf(tmp, 255, "%zu", n);

            ret = tmp;
            ret += make_many();
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
void message(_buffer& b, unsigned long v, const TAIL&... args) {

    unsigned char c = b.consume();

    if (c == '\0') 
        return;

    if (c == 'd') {
        char tmp[256];
        ::snprintf(tmp, 255, "%zu", v);
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

    if (c == 's') {
        parsed_name pn(val.name);
        b.out += pn.make(1, b.is_start);
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


}

#endif
