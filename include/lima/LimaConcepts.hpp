#include <type_traits>
#include <concepts>
#include <string>

namespace lima{

    template<typename T>
    concept ToStringable = requires(T a){
        {std::to_string(a)} -> std::same_as<std::string>;
    };


}