workspace "SPing"
	configurations {"Debug", "Release"}
	architecture "x64"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
thirdpart = "%{wks.location}/" .. "ThirdPart/"
spdlog = thirdpart .. "spdlog/"

project "SPing"
	kind "SharedLib"
	location "SPing"
	language "C++"
	targetdir ("bin/" .. outputdir .. "%{prj.name}")
	objdir  ("bin-tmp/" .. outputdir .. "%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		spdlog .. "include/"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SP_PLATFORM_WIN",
			"SP_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/SandBox")

		}

	filter "configurations:Debug"
		defines {"SP_DEBUG", "_DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"SP_RELEASE", "_RELEASE"}
		optimize "On"


project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "%{prj.name}")
	objdir  ("bin-tmp/" .. outputdir .. "%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		spdlog .. "include/",
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

	filter "configurations:Release"
		defines {"SP_RELEASE", "_RELEASE"}
		optimize "On"