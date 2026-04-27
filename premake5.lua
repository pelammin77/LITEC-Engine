workspace "LITEC Engine"
    configurations { "Debug", "Release" }
    startproject "Sandbox"

project "LITEC"
    kind "SharedLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/LITEC"

    files {
        "LITEC/src/**.h",
        "LITEC/src/**.c",

        "libs/glad/include/**.h",
        "libs/glad/src/**.c",

        "libs/GLFW/include/**.h",
        "libs/cglm/include/**.h",

         "libs/Nuklear/**.h",


        "mylibs/Logger/include/**.h",
        "mylibs/Logger/src/**.c",

        "mylibs/LitecMath/include/**.h",
        "mylibs/LitecMath/src/**.c"


    }

    includedirs {
        "LITEC/src",
        "libs/glad/include",
        "libs/GLFW/include",
        "mylibs/Logger/include",
        "mylibs/LitecMath/include",
        "mylibs/",
        "libs/Nuklear",
        "libs/cglm/include"
    }

    libdirs {
        "libs/GLFW/lib-vc2019"
    }

    links {
        "glfw3",
        "OpenGL32"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG", "LITEC_EXPORTS" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG", "LITEC_EXPORTS" }
        optimize "On"

    filter {}

project "Sandbox"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/Sandbox"

    files {
        "Sandbox/src/**.h",
        "Sandbox/src/**.c",

        "libs/GLFW/include/**.h",
        "mylibs/Logger/include/**.h"
    }

    includedirs {
        "Sandbox/src",
        "LITEC/src",
        "libs/glad/include",
        "libs/GLFW/include",
        "mylibs/Logger/include"
    }

    libdirs {
        "libs/GLFW/lib-vc2019",
        "bin/%{cfg.buildcfg}"
    }

    links {
        "LITEC"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter {}