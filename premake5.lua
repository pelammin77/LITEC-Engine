workspace "LITEC Engine"
    configurations { "Debug", "Release" }
    startproject "SandBox"

project "LITEC"
    kind "SharedLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/LITEC"

    files { "LITEC/src/**.h", "LITEC/src/**.c" }

    includedirs { "libs/glad/include", "libs/GLFW/include" }
    libdirs { "libs/GLFW/lib-vc2019" }

    links { "glfw3", "OpenGL32" }

    filter "configurations:Debug"
        defines { "DEBUG", "LITEC_EXPORTS" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG", "LITEC_EXPORTS" }
        optimize "On"

project "Sandbox"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/Sandbox"

    files { "Sandbox/src/**.h", "Sandbox/src/**.c", "libs/glad/src/glad.c" }

    includedirs { "libs/glad/include", "libs/GLFW/include", "LITEC/src" }
    libdirs { "libs/GLFW/lib-vc2019", "bin/%{cfg.buildcfg}" }
    


    links { "LITEC" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
       

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        postbuildcommands { "copy /Y \"$(SolutionDir)bin\\$(Configuration)\\LITEC.dll\" \"$(SolutionDir)bin\\$(Configuration)\"" }
