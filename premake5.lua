workspace "lima"
    configurations {"Release", "Debug"}

project "lima"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20" -- Might as well
    targetdir "bin/%{cfg.buildcfg}"

    buildoptions {"--std=c++20"}
    buildoptions {"-Werror", "-Wall", "-pedantic", "-Wextra"}
    buildoptions {"-Wno-unused-parameter", "-Wno-unused-result"}

    includedirs {"include/"}

    files {"src/**.c", "src/**.cxx", "src/**.cpp"}
    files {"src/**.h", "src/**.hxx", "src/**.hpp"}

    filter "configurations:Debug"
        symbols "On"
        defines {"DEBUG"}

    filter "configurations:Release"
        optimize "On"
        defines {"NDEBUG"}


