

project "TestMemoryPool"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir (binDir .. outputdir .. "%{prj.name}")
	objdir  (tmpBinDir .. outputdir .. "%{prj.name}")
	defines {}

	files
	{
		"%{Test_memory_pool_root}**.h",
		"%{Test_memory_pool_root}**.cpp",
	}

	includedirs
	{
		Test_memory_pool_root,
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