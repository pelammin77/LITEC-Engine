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
        "LITEC/src/**" -- sisältää kaikki headerit myös alihakemistoista
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
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "Sandbox"
    kind "ConsoleApp"
    language "C"

    files {
        "Sandbox/src/**.h",
        "Sandbox/src/**.c",
        "LITEC/src/Events/EventDispatcher.c",
        "libs/glad/src/glad.c",
        "mylibs/Logger/src/Logger.c"
    }

    includedirs {
        "libs/glad/include",
        "libs/GLFW/include",
        "LITEC/src",       -- sisältää esim. LITEC.h
        "LITEC/src/**",    -- sisältää kaikki alihakemistot
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
        libdirs { "bin/%{cfg.buildcfg}" }  -- ⬅️ lisää tämä!


    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
