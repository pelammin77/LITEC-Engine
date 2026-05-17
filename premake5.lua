workspace "LITEC Engine"
    configurations { "Debug", "Release" }
    startproject "Sandbox"

    filter "system:windows"
        systemversion "latest"

    filter {}


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

        "libs/Nuklear/nuklear.h",
        "libs/Nuklear/demo/glfw_opengl3/nuklear_glfw_gl3.h",

        "mylibs/Logger/include/**.h",
        "mylibs/Logger/src/**.c",

        "mylibs/LitecMath/include/**.h",
        "mylibs/LitecMath/src/**.c"
    }

    includedirs {
        "LITEC/src",

        "libs/glad/include",
        "libs/GLFW/include",
        "libs/cglm/include",

        "libs/Nuklear",
        "libs/Nuklear/demo/glfw_opengl3",

        "mylibs/Logger/include",
        "mylibs/LitecMath/include",
        "mylibs"
    }

    libdirs {
        "libs/GLFW/lib-vc2019"
    }

    links {
        "glfw3",
        "OpenGL32"
    }

    defines {
        "GLFW_INCLUDE_NONE",
        "LITEC_EXPORTS"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter {}


project "Sandbox"
    kind "ConsoleApp"
    language "C"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/Sandbox"

    files {
        "Sandbox/src/**.h",
        "Sandbox/src/**.c"
    }

    includedirs {
        "Sandbox/src",
        "LITEC/src",

        "libs/glad/include",
        "libs/GLFW/include",
        "libs/cglm/include",

        "libs/Nuklear",
        "libs/Nuklear/demo/glfw_opengl3",

        "mylibs/Logger/include",
        "mylibs/LitecMath/include",
        "mylibs"
    }

    libdirs {
        "bin/%{cfg.buildcfg}"
    }

    links {
        "LITEC"
    }

    defines {
        "GLFW_INCLUDE_NONE"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter {}