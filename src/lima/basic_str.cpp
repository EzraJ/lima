#include <iostream>
#include "lima/basic_str.hpp"

namespace lima{
    basic_str::basic_str(size_t nbr_alloc)
    {
        m_nbr_alloc = nbr_alloc;
        m_size = 0;
        m_capacity = 0;
        m_str = (char*)malloc(nbr_alloc * sizeof(char));
        m_capacity = nbr_alloc;
    }


    void basic_str::clear(){
        m_size = 0;
    }

    basic_str::~basic_str()
    {
        free(m_str);
    }


    void basic_str::add(const char* str, size_t nbr)
    {
        if (m_capacity < m_size + nbr)
        {
            m_capacity += m_nbr_alloc;
            m_str = (char *)realloc(m_str, m_capacity * sizeof(char));
        }
        size_t idx_s = 0;
        for (size_t idx = m_size; idx < m_size + nbr; idx++)
        {
            m_str[idx] = str[idx_s];
            idx_s++;
        }
        m_size += nbr;
    }

    void basic_str::moveTo(char* dst){
        for(size_t idx = 0; idx < m_size; idx++){
            dst[idx] = m_str[idx];
        }
    }

    void basic_str::dump()
    {
        for (size_t idx = 0; idx < m_size; idx++)
        {
            std::cout << m_str[idx];
        }
        std::cout << std::endl;
    }
}

