

project "testspdlog"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir (binDir .. outputdir .. "%{prj.name}")
	objdir  (tmpBinDir .. outputdir .. "%{prj.name}")
	defines {}


	files
	{
		"%{testspdlog_root}**.h",
		"%{testspdlog_root}**.cpp",
	}

	includedirs
	{
		testspdlog_root,
		thirdpartIncDir.spdlog,
	}

	links
	{
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
		systemversion "latest"
		staticruntime "On"

		files
		{
		}

		defines
		{
			
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "On"