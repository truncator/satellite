solution "satellite"

	configurations
	{
		"Debug"
	}

	project "satellite"
		kind "ConsoleApp"
		language "C++"

		buildoptions
		{
			"-std=c++11"
		}

		includedirs
		{
			"../Library/stb_image/"
		}

		files
		{
			"../Source/**.hpp",
			"../Source/**.cpp",
			"../Library/stb_image/stb_image.cpp"
		}

		links
		{
			"GL",
			"GLEW",
			"glfw"
		}

		pchheader "../Source/Precompiled.hpp"
		pchsource "../Source/Precompiled.cpp"

		configuration "Debug"
			targetdir "../Binary/Debug/"
			location "../Build/"
			flags { "Symbols", "ExtraWarnings" }
