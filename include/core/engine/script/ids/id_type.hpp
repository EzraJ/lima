#pragma once

#include <stdint.h>
#include <string>
#include <algorithm>
#include <utility>


namespace lima{
    struct IDType{
        std::string prePrint;
        std::string postPrint;
        uint64_t id;
        char visibleRender;

        IDType(){
            prePrint = "";
            postPrint = "";
            id = 0;
            visibleRender = '\0';
        }

        IDType(std::string pre, std::string post, uint64_t _id, char render){
            prePrint = pre;
            postPrint = post;
            id = _id;
            visibleRender = render;
        }

    };
}