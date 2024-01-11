#include <iostream>

#include "fpconvert.hpp"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cout << "Format Error! fpconvert <float>" << std::endl;
        return -1;
    }
    std::cout << "f32 : " << get_float_format(kFloat32) << std::endl;
    std::cout << "f16 : " << get_float_format(kFloat16) << std::endl;
    std::cout << "bf16 : " << get_float_format(kBFloat16) << std::endl;

    float x = std::stof(argv[1]);
    std::cout << "input : " << x << std::endl;

    std::cout << "------------------fp32------------------------" << std::endl;
    print_f32_hex(x);
    print_fp32_bits(x);
    std::cout << "----------------------------------------------" << std::endl;

    std::cout << "------------------fp16------------------------" << std::endl;
    const ushort x_compressed = float_to_half(x);
    print_f16_hex(x_compressed);
    print_fp16_bits(x_compressed);
    std::cout << "----------------------------------------------" << std::endl;

    std::cout << "------------------bf16------------------------" << std::endl;
    const ushort bf16_compressed = float_to_bhalf(x);
    print_f16_hex(bf16_compressed);
    print_bf16_bits(bf16_compressed);
    std::cout << "----------------------------------------------" << std::endl;

    return 0;
}
