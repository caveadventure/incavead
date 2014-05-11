#ifndef __X_LZ77_H
#define __X_LZ77_H

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>

#include <string.h>
#include <stdint.h>

#include <iostream>


namespace lz77 {

inline void push_vlq_uint(size_t n, std::string& out) {

    while (1) {
        unsigned char c = n & 0x7F;
        size_t q = n >> 7;

        if (q == 0) {
            out += c;
            break;
        }

        out += (c | 0x80);
        n = q;
    }
}


inline bool pop_vlq_uint(const unsigned char*& i, const unsigned char* e, size_t& ret) {

    ret = 0;
    size_t off = 0;

    while (1) {

        if (i == e)
            return false;

        unsigned char c = *i;

        if ((c & 0x80) == 0) {
            ret |= (c << off);
            break;
        }

        ret |= ((c & 0x7F) << off);
        off += 7;
        ++i;
    }

    return true;
}

inline size_t substr_run(const unsigned char* ai, const unsigned char* ae,
                         const unsigned char* bi, const unsigned char* be) {

    size_t n = 0;

    while (1) {

        if (*ai != *bi)
            break;

        ++n;
        ++ai;
        ++bi;

        if (ai == ae || bi == be)
            break;
    }

    return n;
}

inline uint32_t pack_4bytes(const unsigned char* i) {

    return (*i | (*(i+1) << 8) | (*(i+2) << 16) | (*(i+3) << 24));
}

inline uint32_t pack_7bytes(const unsigned char* i) {

    return ((*i | (*(i+1) << 8) | (*(i+2) << 16) | (*(i+3) << 24)) +
            (     (*(i+4) << 8) | (*(i+5) << 16) | (*(i+6) << 24)));
}

inline size_t gains(size_t run, size_t offset) {

    size_t gain = run;
    size_t loss = 2;

    if (run > 0x7F) {
        loss++;
    }

    if (run > 0x3fff) {
        loss++;
    }

    if (run > 0x1fffff) {
        loss++;
    }

    if (offset > 0x7F) {
        loss++;
    }

    if (offset > 0x3fff) {
        loss++;
    }

    if (offset > 0x1fffff) {
        loss++;
    }
    

    if (loss > gain)
        return 0;

    return gain - loss;
}

struct offsets_dict_t {

    typedef std::unordered_map< uint32_t, std::vector<size_t> > offsets_t;
    offsets_t offsets;

    size_t maxwindow;

    offsets_dict_t(size_t mw) : maxwindow(mw) {
    }

    void clean() {
        for (offsets_t::iterator i = offsets.begin(); i != offsets.end();) {

            if (i->second.size() == 1) {
                i = offsets.erase(i);
            } else {
                ++i;
            }
        }
    }

    void operator()(uint32_t packed, const unsigned char* i0, const unsigned char* i, const unsigned char* e,
                    size_t& maxrun, size_t& maxoffset, size_t& maxgain) {

        std::vector<size_t>& voffs = offsets[packed];
        voffs.push_back(i - i0);

        if (maxrun > 0)
            return;

        std::vector<size_t>::const_reverse_iterator z = voffs.rbegin();
        ++z;

        size_t nnn = 0;
        while (z != voffs.rend() && nnn < maxwindow) {

            int offset = i - i0 - *z;

            size_t run = substr_run(i, e, i0 + *z, e);
            size_t gain = gains(run, offset);

            if (gain > maxgain) {
                maxrun = run;
                maxoffset = offset;
                maxgain = gain;
            }

            ++z;
            ++nnn;
        }
    }
};


inline std::string compress(const std::string& s, size_t maxskips = 128, size_t blocksize = 100*1024*1024) {

    const unsigned char* i0 = (const unsigned char*)s.data();
    const unsigned char* i = i0;
    const unsigned char* e = i0 + s.size();

    std::string ret;

    std::string unc;

    push_vlq_uint(s.size(), ret);

    offsets_dict_t offsets1(maxskips);
    offsets_dict_t offsets2(maxskips);

    size_t checkpoint = 0;

    while (i != e) {

        unsigned char c = *i;

        if (i > e - 4) {

            unc +=c;
            ++i;
            continue;
        }

        size_t maxrun = 0;
        size_t maxoffset = 0;
        size_t maxgain = 0;

        if (i <= e - 7) {

            uint32_t huge_packed = pack_7bytes(i);
            offsets2(huge_packed, i0, i, e, maxrun, maxoffset, maxgain);
        }

        uint32_t packed = pack_4bytes(i);
        offsets1(packed, i0, i, e, maxrun, maxoffset, maxgain);

        if (maxrun == 0) {
            unc += c;
            ++i;
            continue;
        }

        if (unc.size() > 0) {
            //std::cout << " ==> " << unc.size() << " " << unc << std::endl;

            push_vlq_uint(0, ret);
            push_vlq_uint(unc.size(), ret);
            ret += unc;
            unc.clear();
        }

        //std::cout << "  => " << maxrun << " " << maxoffset << std::endl;

        push_vlq_uint(maxrun, ret);
        push_vlq_uint(maxoffset, ret);
        i += maxrun;

        if (ret.size() - checkpoint > blocksize) {
            offsets1.offsets.clear();
            offsets2.offsets.clear();
            checkpoint = ret.size();
        }
    }

    if (unc.size() > 0) {
        push_vlq_uint(0, ret);
        push_vlq_uint(unc.size(), ret);
        ret += unc;
        unc.clear();
    }

    return ret;
}

struct decompress_t {

    std::string ret;
    unsigned char* out;
    unsigned char* outb;
    unsigned char* oute;


    decompress_t() : out(NULL), outb(NULL), oute(NULL) {}

    bool start(const std::string& s) {

        const unsigned char* i = (const unsigned char*)s.data();
        const unsigned char* e = i + s.size();

        ret.clear();

        size_t size;
        if (!pop_vlq_uint(i, e, size))
            return true;

        ++i;

        ret.resize(size);

        outb = (unsigned char*)ret.data();
        oute = outb + size;
        out = outb;

        return more(i, e);
    }

    bool more(const std::string& s) {

        const unsigned char* i = (const unsigned char*)s.data();
        const unsigned char* e = i + s.size();

        return more(i, e);
    }

    bool more(const unsigned char* i, const unsigned char* e) {

        size_t nunc = 0;
        size_t ncom = 0;

        while (i != e) {

            const unsigned char* zzz = i;

            size_t run;
            if (!pop_vlq_uint(i, e, run))
                return false;

            ++i;

            if (i == e) 
                return false;

            if (run == 0) {

                size_t len;
                if (!pop_vlq_uint(i, e, len))
                    return false;

                ++i;

                //std::cout << ": " << run << " " << len << std::endl;

                if (i == e || i + len > e)
                    return false;
                
                if (out + len > oute)
                    throw std::runtime_error("Malformed data while uncompressing");

                ::memcpy(out, &(*i), len);
                out += len;
                i += len;

                nunc += (i - zzz);

            } else {

                size_t offset;
                if (!pop_vlq_uint(i, e, offset))
                    return false;

                ++i;

                //std::cout << "| " << run << " " << offset << std::endl;

                unsigned char* outi = out - offset;

                if (outi < outb || out + run > oute)
                    throw std::runtime_error("Malformed data while uncompressing");

                if (outi + run < out) {
                    ::memcpy(out, outi, run);
                    out += run;

                } else {

                    while (run > 0) {
                        *out = *outi;
                        ++out;
                        ++outi;
                        --run;
                    }
                }

                ncom += (i - zzz);
            }
        }

        std::cout << " %unc " << nunc << " %com " << ncom << std::endl;

        if (out == oute)
            return true;

        return false;
    }

    const std::string& result() const {
        return ret;
    }
};

}

#endif

