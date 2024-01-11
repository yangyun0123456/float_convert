add_rules("mode.debug", "mode.release")

target("convert_test")
    set_kind("binary")
    add_includedirs("src")
    add_files("fpconvert.cpp")
