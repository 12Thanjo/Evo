-- premake5.lua

workspace "testing"

	configurations{
		"Debug",
		"Release"
	}

	flags{
		"MultiProcessorCompile",
		"NoPCH",
	}

	startproject "testing"

	warnings "High"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		optimize "Off"

		defines{
			"EVO_CONFIG_DEBUG",
			"_DEBUG",
		}
	filter {}

	
	filter "configurations:Release"
		runtime "Release"
		symbols "Off"
		optimize "Full"

		defines{
			"NDEBUG",
		}

		flags{
			"LinkTimeOptimization",
		}
	filter {}



----------------------------------------------
-- projects

project "init"
	kind "Makefile"

	buildcommands {
		( "mkdir -p ./obj/Debug" ),
		( "mkdir -p ./obj/Release" ),

		( "mkdir -p ./bin/Debug" ),
		( "mkdir -p ./bin/Release" ),
	}

	cleancommands{
		( "rm -rf ./obj/" ),
		( "rm -rf ./bin/" ),

		("@echo \"Clean testing may have an error - don't worry, its fine (it seems to be a bug in the genation from premake5)\""),
		("@echo"),
	}

project "*"




project "testing"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	-- stl "libc++"
	exceptionhandling "Off"
	allmodulespublic "Off"

	files {
		"./main.cpp",

		"../Evo.h",
		"../defines.h",

		"../containers/**.h",

		"../tools/**.h",
		"../tools/**.cpp",

		"../utils/**.h",
	}

	includedirs{
		"../",
	}
	
project "*"



project "run"
	kind "Makefile"

	buildcommands {
		( " \"./bin/%{cfg.buildcfg}/testing\" " ),
	}

project "*"


project "test"
	kind "Makefile"

	links{
		"init",
		"testing",
		"run",
	}

project "*"




project "gdb"
	kind "Makefile"


	links{
		"init",
		"testing",
	}

	buildcommands {
		( " gdb \"./bin/%{cfg.buildcfg}/testing\" " ),
	}

project "*"




