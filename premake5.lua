local environment = require "environment"

workspace "imquery"
    configurations{ "Debug", "Release" }

project "libimq"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files {"include/imq/**.hpp", "src/imq/**.cpp"}
    includedirs {"include/imq"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

project "testimq"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files {"include/test/**.hpp", "src/test/**.cpp"}
    includedirs {"include", environment.GTEST_PATH .. "/" .. environment.GTEST_INCLUDE_DIR}
    libdirs {"bin", environment.GTEST_PATH .. "/" .. environment.GTEST_LIB_DIR}
    links {"libimq", environment.GTEST_LIB}

    defines {"IMQ_LIB_IMPORT"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"