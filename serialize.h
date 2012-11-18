#ifndef __SERIALIZE_H
#define __SERIALIZE_H

#include <iostream>
#include <fstream>

#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>

namespace serialize {

struct Sink {
    std::ofstream out;

    Sink(const std::string& name) {

	out.exceptions(std::ofstream::failbit|std::ofstream::badbit);
	out.open(name, std::ios::out|/*std::ios::app|*/std::ios::binary|std::ios::trunc);
    }

    ~Sink() { out.close(); }

    template <typename T>
    void operator<<(const T& t) {
        out << t << "\n";
    }
};

struct Source {
    std::ifstream inp;
    
    Source(const std::string& name) {
	inp.exceptions(std::ifstream::failbit|std::ifstream::badbit);
	inp.open(name, std::ios::in|std::ios::binary);
    }

    ~Source() { inp.close(); }

    template <typename T>
    void operator>>(T& t) {
        inp >> t;
    }
};

template <typename T>
struct reader;

template <typename T>
struct writer;

struct writer_default {
    template <typename T>
    void write(Sink& s, const T& t) {
        s<<t;
    }
};

struct reader_default {
    template <typename T>
    void read(Source& s, T& t) {
        s>>t;
    }
};

//////////////

template <> struct reader<bool> : public reader_default {};
template <> struct reader<int> : public reader_default {};
template <> struct reader<unsigned int> : public reader_default {};
template <> struct reader<long> : public reader_default {};
template <> struct reader<unsigned long> : public reader_default {};
template <> struct reader<long long> : public reader_default {};
template <> struct reader<unsigned long long> : public reader_default {};
template <> struct reader<float> : public reader_default {};
template <> struct reader<double> : public reader_default {};

template <> struct writer<bool> : public writer_default {};
template <> struct writer<int> : public writer_default {};
template <> struct writer<unsigned int> : public writer_default {};
template <> struct writer<long> : public writer_default {};
template <> struct writer<unsigned long> : public writer_default {};
template <> struct writer<long long> : public writer_default {};
template <> struct writer<unsigned long long> : public writer_default {};
template <> struct writer<float> : public writer_default {};
template <> struct writer<double> : public writer_default {};


//////////////

template <>
struct writer<char> {
    void write(Sink& s, const char& t) {
        s << (int)t;
    }
};

template <>
struct writer<unsigned char> {
    void write(Sink& s, const unsigned char& t) {
        s << (int)t;
    }
};

template <>
struct reader<char> {
    void read(Source& s, char& t) {
        int i;
        s >> i;
        t = i;
    }
};

template <>
struct reader<unsigned char> {
    void read(Source& s, unsigned char& t) {
        int i;
        s >> i;
        t = i;
    }
};

//////////////

template <>
struct writer<std::string> {
    void write(Sink& s, const std::string& t) {
        s << t.size();
        for (char c : t) {
            s.out << c;
        }
    }
};

template <>
struct reader<std::string> {
    void read(Source& s, std::string& t) {
        size_t n;
        s >> n;
        t.clear();

        s >> std::noskipws;
        // Read the trailing newline.
        char c;
        s.inp >> c;

        for (size_t i = 0; i < n; ++i) {
            char c;
            s.inp >> c;
            t += c;
        }
        s >> std::skipws;
    }
};

//////////////

template <typename T1, typename T2>
struct writer< std::pair<T1,T2> > {
    void write(Sink& s, const std::pair<T1,T2>& v) {
        writer<T1>().write(s, v.first);
        writer<T2>().write(s, v.second);
    }
};

template <typename T1, typename T2>
struct reader< std::pair<T1,T2> > {
    void read(Source& s, std::pair<T1,T2>& v) {
        reader<T1>().read(s, v.first);
        reader<T2>().read(s, v.second);
    }
};


template <typename T>
struct remove_constpair { typedef T type; };

template <typename T1, typename T2>
struct remove_constpair< std::pair<const T1, T2> > { typedef std::pair<T1, T2> type; };

template <typename T>
inline void write_stl(Sink& s, const T& v) {
    s<<v.size();
    for (const auto& i : v) {
        writer<typename remove_constpair<typename T::value_type>::type>().write(s, i);
    }
}

template <typename T>
inline void read_stl(Source& s, T& v) {
    size_t sz;
    s>>sz;
    v.clear();
    for (size_t i = 0; i < sz; ++i) {
        typename remove_constpair<typename T::value_type>::type vv;
        reader<decltype(vv)>().read(s, vv);
        v.insert(v.end(), vv);
    }
}


template <typename T>
struct writer< std::vector<T> > {
    void write(Sink& s, const std::vector<T>& v) {
        write_stl(s, v);
    }
};

template <typename K,typename V>
struct writer< std::map<K,V> > {
    void write(Sink& s, const std::map<K,V>& v) {
        write_stl(s, v);
    }
};

template <typename T>
struct writer< std::unordered_set<T> > {
    void write(Sink& s, const std::unordered_set<T>& v) {
        write_stl(s, v);
    }
};

template <typename K,typename V>
struct writer< std::unordered_map<K,V> > {
    void write(Sink& s, const std::unordered_map<K,V>& v) {
        write_stl(s, v);
    }
};


template <typename T>
struct reader< std::vector<T> > {
    void read(Source& s, std::vector<T>& v) {
        read_stl(s, v);
    }
};

template <typename K,typename V>
struct reader< std::map<K,V> > {
    void read(Source& s, std::map<K,V>& v) {
        read_stl(s, v);
    }
};

template <typename T>
struct reader< std::unordered_set<T> > {
    void read(Source& s, std::unordered_set<T>& v) {
        read_stl(s, v);
    }
};

template <typename K,typename V>
struct reader< std::unordered_map<K,V> > {
    void read(Source& s, std::unordered_map<K,V>& v) {
        read_stl(s, v);
    }
};


template <typename T>
inline void write(Sink& s, const T& t) {
    writer<T>().write(s, t);
}

template <typename T>
inline void read(Source& s, T& t) {
    reader<T>().read(s, t);
}


}

/**

namespace serialize {

template <>
struct reader<> {
    void read(Source& s, & t) {
        serialize::read(s, t.);
    }
};

template <>
struct writer<> {
    void write(Sink& s, const & t) {
        serialize::write(s, t.);
    }
};

}

**/


#endif
