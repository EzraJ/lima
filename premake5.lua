workspace "lima"
	configurations {"Release", "Debug"}

project "lima"
-- premake5 stuff
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++20"
	targetdir "bin/%{cfg.buildcfg}"
	includedirs {"src/", "include", "vendor/", "./"}

-- buildoptions
    buildoptions {"--std=c++20"}
	buildoptions {"-Werror", "-Wall", "-pedantic", "-Wextra"}
	buildoptions {"-pthread"}
	--buildoptions {"./lib/libangelscript.a"} -- fuck you angel script lmao
	--buildoptions {"/usr/local/lib/libangelscript.a"} -- double fuck you
	--buildoptions

-- libs
	libdirs {"lib/"}
	libdirs {"/usr/local/lib/"}

-- links
	--links {lib/}
	links {"/usr/local/lib/angelscript"}
	--links "angelscript"

-- files
	files {"src/**.c", "src/**.cpp", "src/**.cxx"}
	files {"src/**.h", "src/**.hpp", "src/**.hxx"}

	files {"include/**.c", "include/**.cpp", "include/**.cxx"}
	files {"include/**.h", "include/**.hpp", "include/**.hxx"}

	files {"vendor/**.c", "vendor/**.cpp", "vendor/**.cxx"}
	files {"vendor/**.h", "vendor/**.hpp", "vendor/**.hxx"}
    
	

	
-- filters
	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"

	filter "files:vendor/**"
		buildoptions{"-Wno-error", "-w"}