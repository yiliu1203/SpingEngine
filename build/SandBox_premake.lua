project "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir (binDir ..outputdir .. "%{prj.name}")
	objdir (tmpBinDir .. outputdir .. "%{prj.name}")

	files
	{
		SandBox_root .. "src/**.h",
		SandBox_root .. "src/**.cpp"
	}

	includedirs
	{
		spdlog_root .. "include/",
		SPing_root .. "/src"
	}

	links
	{
		"SPing"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SP_PLATFORM_WIN",
		}

		postbuildcommands
		{

		}

	filter "configurations:Debug"
		defines {"SP_DEBUG", "_DEBUG"}
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines {"SP_RELEASE", "_RELEASE"}
		optimize "On"
		buildoptions "/MD"