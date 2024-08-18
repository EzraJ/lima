#pragma once
#include <stdlib.h>

namespace lima{
    class basic_str{
    public:
        basic_str(size_t nbr_alloc);
        ~basic_str();
        size_t m_size;
        size_t m_capacity;
        size_t m_nbr_alloc;
        char *m_str;
        void add(const char* str, size_t nbr);
        void dump();
        void clear();
        void moveTo(char* dst);
    };
}