project "GLFW"
	kind "staticLib"
	language "C"
	targetdir (binDir .. outputdir .. "%{prj.name}")
	objdir  (tmpBinDir .. outputdir .. "%{prj.name}")

	files
	{
		"../GLFW/include/../GLFW/glfw3.h",
		"../GLFW/include/../GLFW/glfw3native.h",
		"../GLFW/src/glfw_config.h",
		"../GLFW/src/context.c",
		"../GLFW/src/init.c",
		"../GLFW/src/input.c",
		"../GLFW/src/monitor.c",
		"../GLFW/src/vulkan.c",
		"../GLFW/src/window.c"

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
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"../GLFW/src/win32_init.c",
			"../GLFW/src/win32_joystick.c",
			"../GLFW/src/win32_monitor.c",
			"../GLFW/src/win32_time.c",
			"../GLFW/src/win32_thread.c",
			"../GLFW/src/win32_window.c",
			"../GLFW/src/wgl_context.c",
			"../GLFW/src/egl_context.c",
			"../GLFW/src/osmesa_context.c"

		}

		defines
		{
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "On"