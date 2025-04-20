workspace "LITEC Engine"
    configurations { "Debug", "Release" }
    startproject "Sandbox"

    -- Output directories
    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin-int/%{cfg.buildcfg}/%{prj.name}")

project "LITEC"
    kind "SharedLib"
    language "C"

    files {
        "LITEC/src/**.h",
        "LITEC/src/**.c",
        "libs/glad/src/glad.c",
        "mylibs/Logger/src/Logger.c"
    }

    includedirs {
        "libs/glad/include",
        "libs/GLFW/include",
        "mylibs/Logger/include",
        "LITEC/src"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "LITEC_PLATFORM_WINDOWS", "LITEC_EXPORTS" }
        links { "glfw3", "OpenGL32" }
        libdirs { "libs/GLFW/lib-vc2019" }

    filter "system:linux"
        defines { "LITEC_PLATFORM_LINUX", "LITEC_EXPORTS" }
        links { "glfw", "GL", "m", "dl" }
        buildoptions { "-Wall", "-Wextra" }

    filter "configurations:Debug"
        defines { "DEBUG", "LITEC_EXPORTS" } -- tärkeä: exports vain LITEC-projektiin!
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG", "LITEC_EXPORTS" }
        optimize "On"

project "Sandbox"
    kind "ConsoleApp"
    language "C"

    files {
        "Sandbox/src/**.h",
        "Sandbox/src/**.c"
    }

    includedirs {
        "libs/glad/include",
        "libs/GLFW/include",
        "LITEC/src",
        "mylibs/Logger/include"
    }

    links { "LITEC" }
    dependson { "LITEC" }

    filter "system:windows"
        systemversion "latest"
        defines { "LITEC_PLATFORM_WINDOWS" }
        libdirs { "libs/GLFW/lib-vc2019", "bin/%{cfg.buildcfg}" }
        links { "glfw3", "OpenGL32" }

    filter "system:linux"
        defines { "LITEC_PLATFORM_LINUX" }
        links { "glfw", "GL", "m", "dl" }
        libdirs { "bin/%{cfg.buildcfg}" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
