add_rules("mode.debug", "mode.release")

target("fp32_to_16")
    set_kind("binary")
    add_includedirs("src")
    add_files("fp32_to_f16.cpp")

target("fp16_to_fp32")
    set_kind("binary")
    add_includedirs("src")
    add_files("fp16_to_fp32.cpp")

target("bf16_to_fp32")
    set_kind("binary")
    add_includedirs("src")
    add_files("bf16_to_fp32.cpp")

target("hex_to_fp32")
    set_kind("binary")
    add_includedirs("src")
    add_files("hex_to_fp32.cpp")
