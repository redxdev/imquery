local environment = require "environment"

workspace "imquery"
    configurations{ "Debug", "Release" }
    startproject "testimq"
    flags { "C++11" }
    filter "system:windows"
        defines {"_CRT_SECURE_NO_WARNINGS" }

project "imq"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files {
        "include/imq/**.h",
        "src/imq/**.cpp",
        "grammar/imq/grammar/IMQLangBaseListener.cpp",
        "grammar/imq/grammar/IMQLangBaseListener.h",
        "grammar/imq/grammar/IMQLangLexer.cpp",
        "grammar/imq/grammar/IMQLangLexer.h",
        "grammar/imq/grammar/IMQLangListener.cpp",
        "grammar/imq/grammar/IMQLangListener.h",
        "grammar/imq/grammar/IMQLangParser.cpp",
        "grammar/imq/grammar/IMQLangParser.h"
    }
    includedirs {"include/imq", "grammar", environment.ANTLR_CPP_PATH}
    links {environment.ANTLR_LIB}
    defines {"_SCL_SECURE_NO_WARNINGS"}

    prebuildcommands {
        "{ECHO} Cleaning grammar",
        "{RMDIR} grammar/imq/grammar",
        "{ECHO} Building grammar",
        environment.ANTLR_CMD .. " -o grammar/imq/grammar -package imq -Dlanguage=Cpp IMQLang.g4"
    }

    filter "configurations:Debug"
	libdirs {environment.ANTLR_DEBUG_LIB_DIR}
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        libdirs {environment.ANTLR_RELEASE_LIB_DIR}
        defines {"NDEBUG"}
        optimize "On"
		
project "iqc"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files {"include/iqc/**.h", "src/iqc/**.cpp"}
    includedirs {"include", "include/iqc", "include/iqc/thirdparty", "grammar", environment.ANTLR_CPP_PATH}
    libdirs {"bin"}
    links {"imq", environment.ANTLR_LIB}

    filter "configurations:Debug"
        libdirs {environment.ANTLR_DEBUG_LIB_DIR}
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        libdirs {environment.ANTLR_RELEASE_LIB_DIR}
        defines {"NDEBUG"}
        optimize "On"
		
project "testimq"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files {"include/test/**.h", "src/test/**.cpp"}
    includedirs {"include", "include/test", "grammar", environment.GTEST_PATH .. "/" .. environment.GTEST_INCLUDE_DIR, environment.ANTLR_CPP_PATH}
    libdirs {"bin"}
    links {"imq", environment.GTEST_LIB, environment.ANTLR_LIB}

    filter "configurations:Debug"
        libdirs {environment.GTEST_PATH .. "/" .. environment.GTEST_DEBUG_LIB_DIR, environment.ANTLR_DEBUG_LIB_DIR}
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        libdirs {environment.GTEST_PATH .. "/" .. environment.GTEST_RELEASE_LIB_DIR, environment.ANTLR_RELEASE_LIB_DIR}
        defines {"NDEBUG"}
        optimize "On"

    filter "system:linux"
        links {"pthread"}
