// For the sake of simplicity, a block is one "unit", or "character", in the world. 

#pragma once

#include <cstdint>

#include "utils/vector2.hpp"
#include <memory.h>

namespace lima{
    namespace core{
        namespace engine{
            class block{
                public:
                    block(vector2 pos, uint64_t id, char inChar);
                    ~block(){}
                    
                    vector2 getPos();
                    char getRender();
                    uint64_t getID();
                    void changeID(uint64_t id);
                    void swapPosition(block& other);
                    //friend void swap(block& lhs, block& rhs){
                     //   std::swap(lhs._pos, rhs._pos);
                      //  std::swap(lhs._id, rhs._id);
                       // std::swap(lhs._myChar, rhs._myChar);
                    //}

                    bool transparent(){
                        return !_id; // 0 -> true, anything else -> false
                    }

                private:
                    uint64_t _id = 0;
                    vector2 _pos = vector2(0,0);
                    char _myChar;
            };
        }
    }
}
