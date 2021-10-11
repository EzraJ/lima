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
                    ~block(){

                    }

                    vector2 getPos();

                    char getRender();
                    uint64_t getID();
                    void changeID(uint64_t id);
                    void swapPosition(block& other);

                    vector2 getPos(){
                        return _pos;
                    }

                    block(vector2 pos, uint64_t id, char inChar){
                        _id = id;
                        _pos = pos;
                        _myChar = inChar;
                    }

                    char getRender(){
                        return _myChar;
                    }

                    uint64_t getID(){
                        return _id;
                    }

                    ~block(){

                    }

                    void changeID(uint64_t id){
                        _id = id;
                    }

                    void swapPosition(block& other){ // We don't ever want a space "without a block", so *always* swap instead of changing position
                        std::swap(this->_pos, other._pos);
                        std::swap(this->_id, other._id);
                        std::swap(this->_myChar, other._myChar);
                    }
                private:
                uint64_t _id = 0;
                vector2 _pos = vector2(0,0);
                char _myChar;
            };
        }
    }
}