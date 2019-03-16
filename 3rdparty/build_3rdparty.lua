project "3rdparty"
	kind "StaticLib"
	language "C++"
	
	includedirs { PROJECT_ROOT_DIR .. "/3rdparty/" }
	files { "**.cpp", "**.c" ,"**.h" }