project "GLFW"
	kind "staticLib"
	language "C"
	targetdir ("bin/" .. outputdir .. "%{prj.name}")
	objdir  ("bin-tmp/" .. outputdir .. "%{prj.name}")

	files
	{

	}

	filter "system:linux"

		pic "On"
		systemversion "latest"
		staticruntime "On"
		files
		{
			"include/GLFW/glfw3.h",
			"include/GLFW/glfw3native.h",
			"src/glfw_config.h",
			"src/context.c",
			"src/init.c",
			"src/input.c",
			"src/monitor.c",
			"src/vulkan.c",
			"src/window.c"

		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"GLFW/src/x11_init.c",
			"GLFW/src/x11_monitor.c",
			"GLFW/src/x11_window.c",
			"GLFW/src/xkb_unicode.c",
			"GLFW/src/posix_time.c",
			"GLFW/src/posix_thread.c",
			"GLFW/src/glx_context.c",
			"GLFW/src/egl_context.c",
			"GLFW/src/osmesa_context.c",
			"GLFW/src/linux_joystick.c"

		}

		defines
		{
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configuration:Debug"
		runtime "Debug"
		symbols "On"
	
	filter "configuration:Release"
		runtime "Release"
		optimize "On"