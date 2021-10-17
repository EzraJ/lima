#pragma once
#include <iostream>
#include "core/engine/script/scriptEngine.hpp"

namespace lima{
    namespace script{
        namespace limaFunc{
            void print(const std::string& in){
                std::cout << in;
            }

            uint64_t RegisterIDType(std::string pre, std::string post, uint64_t _id, char render){
                lima::script::_idTypes[_id] = IDType(pre, post, _id, render);
                return _id;
            }

            IDType getID(uint64_t _id){
                return lima::script::_idTypes[_id];
            }

        }
    }
}