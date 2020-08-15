workspace "SPing"
	configurations {"Debug", "Release"}
	architecture "x64"

-- 绝对路径----
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
thirdpart = "%{wks.location}/" .. "ThirdPart/"
testdir = "%{wks.location}/" .. "Test/"
exampleDir = "%{wks.location}/" .. "Example/"

spdlog_root = thirdpart .. "spdlog/"
GLFW_root = thirdpart .. "GLFW/"
testspdlog_root = testdir .. "Testspdlog/"

thirdpartIncDir = {}
thirdpartIncDir["GLFW"] = thirdpart .. "GLFW/include"
thirdpartIncDir["spdlog"] = thirdpart .. "spdlog/include"


binDir = "%{wks.location}/bin/"
tmpBinDir = "%{wks.location}/bin-tmp/"

-- 相对路径--
---

dofile "projects/glfw_premake.lua"
dofile "projects/spdlog_premake.lua"
dofile "projects/testspdlog_premake.lua"

project "SPing"
	kind "SharedLib"
	location "SPing"
	language "C++"
	cppdialect "C++17"
	targetdir (binDir .. outputdir .. "%{prj.name}")
	objdir  (tmpBinDir .. outputdir .. "%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		spdlog_root .. "include/",
		"%{prj.name}/src",
		thirdpartIncDir.GLFW,
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	pchheader "SPingPre.h"
	pchsource "SPing/src/SPingPre.cpp" 

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SP_PLATFORM_WIN",
			"SP_BUILD_DLL",
			"SP_ENABLE_ASSERT",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/SandBox")
		}

	filter "configurations:Debug"
		defines {"SP_DEBUG", "_DEBUG"}
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines {"SP_RELEASE", "_RELEASE"}
		optimize "On"
		buildoptions "/MD"


project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir ("bin/" .. outputdir .. "%{prj.name}")
	objdir  ("bin-tmp/" .. outputdir .. "%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		spdlog_root .. "include/",
		"SPing/src"
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