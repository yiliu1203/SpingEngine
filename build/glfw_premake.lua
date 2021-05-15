project "GLFW"
	kind "staticLib"
	language "C"
	targetdir (binDir .. outputdir .. "%{prj.name}")
	objdir  (tmpBinDir .. outputdir .. "%{prj.name}")

	files
	{
		GLFW_root .. "include/../GLFW/glfw3.h",
		GLFW_root .. "include/../GLFW/glfw3native.h",
		GLFW_root .. "src/glfw_config.h",
		GLFW_root .. "src/context.c",
		GLFW_root .. "src/init.c",
		GLFW_root .. "src/input.c",
		GLFW_root .. "src/monitor.c",
		GLFW_root .. "src/vulkan.c",
		GLFW_root .. "src/window.c"

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
			GLFW_root .. "src/win32_init.c",
			GLFW_root .. "src/win32_joystick.c",
			GLFW_root .. "src/win32_monitor.c",
			GLFW_root .. "src/win32_time.c",
			GLFW_root .. "src/win32_thread.c",
			GLFW_root .. "src/win32_window.c",
			GLFW_root .. "src/wgl_context.c",
			GLFW_root .. "src/egl_context.c",
			GLFW_root .. "src/osmesa_context.c"

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