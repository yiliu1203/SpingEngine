

project "spdlog"
	kind "staticLib"
	language "C++"
	cppdialect "C++17"
	targetdir (binDir .. outputdir .. "%{prj.name}")
	objdir  (tmpBinDir .. outputdir .. "%{prj.name}")
	defines {"SPDLOG_COMPILED_LIB"}

	files
	{
		spdlog_root .. "include/**.h",
		spdlog_root .. "src/**.cpp",

	}

	includedirs
	{
		spdlog_root .. "include/",
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