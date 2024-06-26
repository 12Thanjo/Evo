-- premake5.lua

workspace "testing"

	configurations{
		"Debug",
		"Release"
	}

	platforms{
		"Windows",
		"Linux",
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





config = {
	location = ("%{wks.location}"),
	platform = ("%{cfg.platform}"),
	build    = ("%{cfg.buildcfg}"),
	project  = ("%{prj.name}"),
}


target = {
	bin = string.format("%s/build/%s/%s/bin/",   config.location, config.platform, config.build),
	obj = string.format("%s/build/%s/%s/obj/%s", config.location, config.platform, config.build, config.project),
}



----------------------------------------------
-- projects

project "init"
	kind "Makefile"

	buildcommands {
		string.format("mkdir -p %s", target.bin),
		string.format("mkdir -p %s", target.obj),
	}

	cleancommands{
		( "rm -rf ./build/" ),

		("@echo \"\\\"Clean testing\\\" may have an error - don't worry, its fine (it seems to be a bug in the genation from premake5)\""),
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

	targetdir(target.bin)
	objdir(target.obj)

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
		(target.bin .. "testing.exe"),
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
		string.format(" gdb \"%s/testing.exe\" ", target.bin),
	}

project "*"




