

project "TestOthers"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir (binDir .. outputdir .. "%{prj.name}")
	objdir  (tmpBinDir .. outputdir .. "%{prj.name}")
	defines {}

	files
	{
		"%{test_others_root}**.h",
		"%{test_others_root}**.cpp",
	}

	includedirs
	{
		test_others_root,
		spdlog_root .. "include/",
		SPing_root .. "/src"
	}

	links
	{
		"SPing"
	}

	filter "system:linux"

		pic "On"
		systemversion "latest"
		staticruntime "On"
		files
		{

		}

		defines
		{
			
		}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "On"

		files
		{
		}

		defines
		{
			"SP_PLATFORM_WIN",
			
		}

	filter "configurations:Debug"
		runtime "Debug"
		defines {"SP_DEBUG", "_DEBUG"}
		symbols "On"
		buildoptions "/MDd"
	
	filter "configurations:Release"
		runtime "Release"
		defines {"SP_RELEASE", "_RELEASE"}
		optimize "On"
		buildoptions "/MD"