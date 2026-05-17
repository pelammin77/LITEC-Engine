workspace "LITEC Engine"
    configurations { "Debug", "Release" }
    startproject "Sandbox"

    filter "system:windows"
        systemversion "latest"

    filter {}


-- Common paths
GLFW_INCLUDE_DIR = "libs/GLFW/include"
GLAD_INCLUDE_DIR = "libs/glad/include"
CGLM_INCLUDE_DIR = "libs/cglm/include"
NUKLEAR_DIR = "libs/Nuklear"
NUKLEAR_GLFW_OPENGL3_DIR = "libs/Nuklear/demo/glfw_opengl3"

LOGGER_INCLUDE_DIR = "mylibs/Logger/include"
LOGGER_SRC_DIR = "mylibs/Logger/src"

LITEC_MATH_INCLUDE_DIR = "mylibs/LitecMath/include"
LITEC_MATH_SRC_DIR = "mylibs/LitecMath/src"

MSYS2_INCLUDE_DIR = "C:/msys64/ucrt64/include"
MSYS2_LIB_DIR = "C:/msys64/ucrt64/lib"


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

        GLAD_INCLUDE_DIR,
        GLFW_INCLUDE_DIR,
        CGLM_INCLUDE_DIR,

        NUKLEAR_DIR,
        NUKLEAR_GLFW_OPENGL3_DIR,

        LOGGER_INCLUDE_DIR,
        LITEC_MATH_INCLUDE_DIR,
        "mylibs",

        MSYS2_INCLUDE_DIR
    }

    libdirs {
        MSYS2_LIB_DIR
    }

    links {
        "glfw3",
        "opengl32",
        "gdi32",
        "user32",
        "shell32"
    }

    defines {
        "LITEC_EXPORTS",
        "GLFW_INCLUDE_NONE"
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

        GLAD_INCLUDE_DIR,
        GLFW_INCLUDE_DIR,
        CGLM_INCLUDE_DIR,

        NUKLEAR_DIR,
        NUKLEAR_GLFW_OPENGL3_DIR,

        LOGGER_INCLUDE_DIR,
        LITEC_MATH_INCLUDE_DIR,
        "mylibs",

        MSYS2_INCLUDE_DIR
    }

    libdirs {
        "bin/%{cfg.buildcfg}",
        MSYS2_LIB_DIR
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