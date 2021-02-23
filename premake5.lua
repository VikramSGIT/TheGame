workspace "TheGame"
    architecture "x64"
    startproject "TheGame"

    configurations
    {
        "Release",
        "Debug"
    }

    project "TheGame"
        location ""
        kind "ConsoleApp"
        language "C++"
        staticruntime "Off"

        targetdir("bin/bin")
        objdir("obj/bin")

        files
        {
            "MarsEngine/MarsEngine/src/Vender/imgui/backends/imgui_impl_glfw.cpp",
			"MarsEngine/MarsEngine/src/Vender/imgui/backends/imgui_impl_glfw.h",
			"MarsEngine/MarsEngine/src/Vender/imgui/backends/imgui_impl_opengl3.cpp",
			"MarsEngine/MarsEngine/src/Vender/imgui/backends/imgui_impl_opengl3.h",
			"MarsEngine/MarsEngine/src/Vender/imgui/*.cpp",
			"MarsEngine/MarsEngine/src/Vender/imgui/*.h",
            "MarsEngine/MarsEngine/src/Core/Logger.cpp",
			"MarsEngine/MarsEngine/src/Core/Logger.h",
            "MarsEngine/MarsEngine/src/Addons/**.cpp",
            "MarsEngine/MarsEngine/src/Addons/**.h",
			"MarsEngine/MarsEngine/src/GL/**.h",
			"MarsEngine/MarsEngine/src/RenderAPI/**.cpp",
			"MarsEngine/MarsEngine/src/RenderAPI/**.h",
			"MarsEngine/MarsEngine/src/Utils/**.h",
			"MarsEngine/MarsEngine/src/Utils/**.cpp",
			"MarsEngine/MarsEngine/src/Vender/GLFW/**.h",
			"MarsEngine/MarsEngine/src/Vender/stb/stb_image.h",
			"MarsEngine/MarsEngine/src/Window/**.h",
			"MarsEngine/MarsEngine/src/Window/**.cpp",
			"MarsEngine/MarsEngine/src/MarsHeader.h",
            "*.h",
            "*.cpp"
        }

        includedirs
		{
			"MarsEngine/MarsEngine/src/Vender/imgui",
			"MarsEngine/MarsEngine/src/Vender",
			"MarsEngine/MarsEngine/src",
		}

		flags
		{
			"MultiProcessorCompile"
		}

		filter "system:windows"
			cppdialect "C++17"
			

			defines
			{
				"ME_PLATFORM_WINDOWS",
				"IMGUI_IMPL_OPENGL_LOADER_GLEW",
				"GLFW_INCLUDE_NONE",
				"GLEW_STATIC",
				"_CRT_SECURE_NO_WARNINGS"
			}

			libdirs
			{
				"MarsEngine/bin/Release-x86_64/lib"
			}

			links
			{
				"ImGui",
				"glfw3",
				"glew32s",
				"opengl32"
			}

		filter "configurations:Debug"
			defines "ME_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "ME_RELEASE"
			optimize "On"

        