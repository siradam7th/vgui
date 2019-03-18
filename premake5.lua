PROJECT_ROOT_DIR = path.getabsolute("")

workspace "vGUI"
	configurations { "Debug", "Release", "Production"}
	platforms { "x32", "x64" }
	language "C++"

	objdir "build/bin/%{cfg.platform}_%{cfg.buildcfg}"
	location ("build/" .. _ACTION)
	
	filter "platforms:x32"
		architecture "x32"
		
	filter "platforms:x64"
		architecture "x64"
	
	filter "platforms:Windows"
		defines { "PLATFORM_WIN" }
		
	filter { "platforms:Windows" and "platforms:x32" }
		defines { "PLATFORM_WIN32" }
	
	filter { "platforms:Windows" and "platforms:x64" }
		defines { "PLATFORM_WIN64" }
		
	-- No winsdk workaround is needed any more in the latest build of premake5
	-- please update your premake5 to at least (premake-5.0.0-alpha13) for this functionality to work
	filter {"system:windows", "action:vs*"}
		systemversion("latest")
		
	-- These settings will apply to the entire workspace or project (whichever is active)
	filter {}
		-- Each configuration has its own obj file dir
		objdir ("build/" .. _ACTION .. "/obj")
		-- Disable precompiled headers
		flags { "NoPCH", "NoManifest" }
		cppdialect "C++17" 
		characterset "Unicode"
		
	filter "configurations:Debug"
		defines { "_DEBUG", "VGUI_BUILD_DEBUG" }
		symbols "On"
		
	filter "configurations:Release"
		defines { "NDEBUG", "VGUI_BUILD_RELEASE"}
		symbols "On"
		optimize "On"
		
	filter "configurations:Production"
		defines { "VGUI_BUILD_PRODUCTION" }
		symbols "Off"
		optimize "Full"
		
	-- Enable Full symbols for Debug and Release builds if using VS2017
	filter { "action:vs2017" and "configurations:Debug" or "configurations:Release" }
		symbols "Full" -- Visual Studio 2017 or newer
		
	
	-- Build vgui
	include("vgui/build_vgui.lua")
		
	-- Build 3rdparty libraries
	include("3rdparty/build_3rdparty.lua")
	
	-- Build Example project
	if next(os.matchfiles("example/build_example.lua")) then
		include("example/build_example.lua")
	end