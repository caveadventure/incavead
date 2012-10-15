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
            ::snprintf(tmp, 255, "%ld", n);

            ret = tmp;
            ret += ' ';
            ret += make_many();
        }

        if (capitals && ret.size() > 0) {
            ret[0] = ::toupper(ret[0]);
        }

        return ret;
    }
};


template <typename T>
std::string message(const std::string& tmpl, const T& obj, size_t n = 1) {

    std::string ret;
    bool is_start = true;

    parsed_name pn(obj.name);

    enum {
        TEXT,
        PCT,
        PERIOD
    } state = TEXT;

    for (unsigned char c : tmpl) {

        if (c == '%') {
            state = PCT;

        } else if (c == '.') {
            ret += c;
            state = PERIOD;

        } else {

            switch (state) {
            case TEXT:
                ret += c;
                is_start = false;
                break;

            case PCT:
                if (c == 's') {
                    ret += pn.make(n, is_start);
                } else {
                    ret += c;
                }
                state = TEXT;
                break;

            case PERIOD:
                ret += c;
                if (::isspace(c)) {
                    is_start = true;
                } else {
                    is_start = false;
                }
                break;
            }
        }
    }

    return ret;
}


}

#endif
