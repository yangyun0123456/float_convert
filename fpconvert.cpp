#include <iostream>

#include "fpconvert.hpp"

void print_bits(const ushort x) {
    for(int i=15; i>=0; i--) {
        std::cout << ((x>>i)&1);
        if(i==15||i==10) std::cout << " ";
        if(i==10) std::cout << "      ";
    }
    std::cout << std::endl;
}

void print_bits(const float x) {
    uint b = *(uint*)&x;
    for(int i=31; i>=0; i--) {
        std::cout << ((b>>i)&1);
        if(i==31||i==23) std::cout << " ";
        if(i==23) std::cout << "   ";
    }
    std::cout << std::endl;
}

void print_hex(const float x) {
    unsigned int x_int = ((unsigned int*)(&x))[0];
    printf("0x%04x\n", x_int);
}

void print_hex(const ushort x) {
    printf("0x%02x\n", x);
}

int main(int argc, const char *argv[]) {
    std::cout << "f32 : " << get_float_format(kFloat32) << std::endl;
    std::cout << "f16 : " << get_float_format(kFloat16) << std::endl;

    float x = std::stof(argv[1]);
    std::cout << "input : " << x << std::endl;
    print_hex(x);
    print_bits(x);

    const ushort x_compressed = float_to_half(x);
    print_hex(x_compressed);
    print_bits(x_compressed);

    return 0;
}
