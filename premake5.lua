workspace "lima"
	configurations {"Release", "Debug"}

project "lima"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++20"
    buildoptions "--std=c++20"
	targetdir "bin/%{cfg.buildcfg}"
	includedirs {"src/", "include/", "./", "vendor/"}
    libdirs {"lib/"}
	files {"src/**.cpp", "src/**.c", "include/**.cpp", "include/**.c", "src/**.h", "src/**.hpp", "src/**.hxx", "include/**.h", "include/**.hpp", "include/**.hxx"}
    links {"angelscript"}
	

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"