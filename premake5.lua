workspace "lima"
    configurations {"Release", "Debug"}

project "lima"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20" -- Might as well
    targetdir "bin/%{cfg.buildcfg}"

    buildoptions {"--std=c++20"}
    buildoptions {"-Werror", "-Wall", "-pedantic", "-Wextra"}

    includedirs {"include/"}

    files {"src/**.c", "src/**.cxx", "src/**.cpp"}
    files {"src/**.h", "src/**.hxx", "src/**.hpp"}

    filter "configurations:Debug"
        symbols "On"
        defines {"DEBUG"}

    filter "configurations:Release"
        --optimize "On" Only enabled o2
        buildoptions {"-O3"}
        defines {"NDEBUG"}


