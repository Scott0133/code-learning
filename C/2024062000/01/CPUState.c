#define CSR_COUNT 10

struct CPUState {
    __UINT32_TYPE__ regs[32], csrs[CSR_COUNT];
    __UINT8_TYPE__ *mem;
    __UINT32_TYPE__ men_offset, men_size;
};