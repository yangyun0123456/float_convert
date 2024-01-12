#include <iostream>
#include <sstream>

#include "fpconvert.hpp"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cout << "Format Error! hex_to_fp32 <hex>" << std::endl;
        return -1;
    }
    std::cout << "f32 : " << get_float_format(kFloat32) << std::endl;

    unsigned int x = 0;
    std::stringstream ss;
    ss << std::hex << argv[1];
    ss >> x;
    printf("input : 0x%02x\n", x);

    std::cout << "------------------fp32------------------------" << std::endl;
    print_fp32_bits(x);
    printf("%f\n", as_float(x));
    std::cout << "----------------------------------------------" << std::endl;

    return 0;
}
