#ifndef __FPCONVERT_H__
#define __FPCONVERT_H__

typedef unsigned short ushort;
typedef unsigned int uint;

uint as_uint(const float x) {
    return *(uint*)&x;
}

float as_float(const uint x) {
    return *(float*)&x;
}

void print_fp16_bits(const ushort x) {
    for(int i=15; i>=0; i--) {
        std::cout << ((x>>i)&1);
        if(i==15||i==10) std::cout << " ";
        if(i==10) std::cout << "      ";
    }
    std::cout << std::endl;
}

void print_bf16_bits(const ushort x) {
    for(int i=15; i>=0; i--) {
        std::cout << ((x>>i)&1);
        if(i==15||i==7) std::cout << " ";
        if(i==7) std::cout << "      ";
    }
    std::cout << std::endl;
}

void print_fp32_bits(const float x) {
    uint b = *(uint*)&x;
    for(int i=31; i>=0; i--) {
        std::cout << ((b>>i)&1);
        if(i==31||i==23) std::cout << " ";
        if(i==23) std::cout << "   ";
    }
    std::cout << std::endl;
}

void print_fp32_hex(const float x) {
    unsigned int x_int = as_uint(x);
    printf("0x%04x\n", x_int);
}

void print_f16_hex(const ushort x) {
    printf("0x%02x\n", x);
}

float half_to_float(const ushort x) { // IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
    const uint e = (x&0x7C00)>>10; // exponent
    const uint m = (x&0x03FF)<<13; // mantissa
    const uint v = as_uint((float)m)>>23; // evil log2 bit hack to count leading zeros in denormalized format
    return as_float((x&0x8000)<<16 | (e!=0)*((e+112)<<23|m) | ((e==0)&(m!=0))*((v-37)<<23|((m<<(150-v))&0x007FE000))); // sign : normalized : denormalized
}

ushort float_to_half(const float x) { // IEEE-754 16-bit floating-point format (without infinity): 1-5-10, exp-15, +-131008.0, +-6.1035156E-5, +-5.9604645E-8, 3.311 digits
    const uint b = as_uint(x)+0x00001000; // round-to-nearest-even: add last bit after truncated mantissa
    const uint e = (b&0x7F800000)>>23; // exponent
    const uint m = b&0x007FFFFF; // mantissa; in line below: 0x007FF000 = 0x00800000-0x00001000 = decimal indicator flag - initial rounding
    return (b&0x80000000)>>16 | (e>112)*((((e-112)<<10)&0x7C00)|m>>13) | ((e<113)&(e>101))*((((0x007FF000+m)>>(125-e))+1)>>1) | (e>143)*0x7FFF; // sign : normalized : denormalized : saturate
}

ushort float_to_bhalf(const float x) {
    ushort data = ((unsigned int *)(&x))[0] >> 16;
    return data;
}

float bhalf_to_float(const ushort x) {
    unsigned int proc = x << 16;
    return as_float(proc);
}

enum FLOAT_TYPE {
    kFloat64 = 0,
    kFloat32 = 1,
    kFloat16 = 2,
    kBFloat16 = 3
};

std::string get_float_format(FLOAT_TYPE type) {
    switch (type) {
        case kFloat64:
        return "s:1-e:11-f:52";
        case kFloat32:
        return "s:1-e:8-f:23";
        case kFloat16:
        return "s:1-e:5-f:10";
        case kBFloat16:
        return "s:1-e:8-f:7";
        default:
        return "UNKOWN FORMAT";
    }
}

#endif  // __FPCONVERT_H__
