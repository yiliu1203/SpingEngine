
project "SPing"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	characterset "MBCS"
	targetdir (binDir .. outputdir .. "%{prj.name}")
	objdir  (tmpBinDir .. outputdir .. "%{prj.name}")

	files
	{
		SPing_root .. "src/**.h",
		SPing_root .. "src/**.cpp"
	}

	includedirs
	{
		spdlog_root .. "include/",
		SPing_root .. "src/",
		thirdpartIncDir.GLFW,
	}

	links
	{
	}

	-- pchheader (SPing_root .. "src/SPingPre.h")
	-- pchsource (SPing_root .. "src/SPingPre.cpp") 

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SP_PLATFORM_WIN",
			"SP_ENABLE_ASSERT",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/SandBox"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/TestOthers")
		}

	filter "configurations:Debug"
		defines {"SP_DEBUG", "_DEBUG"}
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines {"SP_RELEASE", "_RELEASE"}
		optimize "On"
		buildoptions "/MD"