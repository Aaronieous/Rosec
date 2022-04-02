workspace "Rosec"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLAD"] = "Rosec/vendor/GLAD/include"
	IncludeDir["GLFW"] = "Rosec/vendor/GLFW/include"
	IncludeDir["ImGui"] = "Rosec/vendor/imgui"
	IncludeDir["glm"] = "Rosec/vendor/glm/glm"

	include "Rosec/vendor/GLAD"
	include "Rosec/vendor/GLFW"
	include "Rosec/vendor/imgui"

	project "Rosec"
		location "Rosec"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "rscpch.h"
		pchsource "%{prj.name}/src/rscpch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}"
		}

		links
		{
		"GLAD",
		"GLFW",
		"ImGui",
		"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "Off"
			systemversion "latest"

			defines
			{
			"RSC_BUILD_DLL",
			"RSC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}

		filter "configurations:Debug"
			defines "RSC_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "RSC_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "RSC_DIST"
			runtime "Release"
			optimize "On"


	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Rosec/vendor/spdlog/include",
			"Rosec/src"
		}

		links
		{
			"Rosec"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "Off"
			systemversion "latest"

			defines
			{
			"RSC_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "RSC_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "RSC_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "RSC_DIST"
			runtime "Release"
			optimize "On"