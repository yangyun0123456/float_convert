add_rules("mode.debug", "mode.release")

set_languages("c++23")

target("fpconvert")
    set_kind("binary")
    add_includedirs("src")
    add_files("fpconvert.cpp")
