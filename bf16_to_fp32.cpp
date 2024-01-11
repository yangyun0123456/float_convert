#include <iostream>
#include <sstream>

#include "fpconvert.hpp"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cout << "Format Error! bf16_to_fp32 <bf16 hex>" << std::endl;
        return -1;
    }
    std::cout << "f32 : " << get_float_format(kFloat32) << std::endl;
    std::cout << "bf16 : " << get_float_format(kBFloat16) << std::endl;

    unsigned int x = 0;
    std::stringstream ss;
    ss << std::hex << argv[1];
    ss >> x;
    printf("input : 0x%02x\n", x);

    std::cout << "------------------bf16------------------------" << std::endl;
    print_f16_hex(x);
    print_bf16_bits(x);
    std::cout << "----------------------------------------------" << std::endl;

    float x_uncompressed = bhalf_to_float(x);
    std::cout << "------------------f32-------------------------" << std::endl;
    print_fp32_hex(x_uncompressed);
    print_fp32_bits(x_uncompressed);
    printf("%f\n", x_uncompressed);
    std::cout << "----------------------------------------------" << std::endl;

    return 0;
}
