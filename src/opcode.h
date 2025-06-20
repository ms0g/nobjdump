#ifndef OPCODE_H
#define OPCODE_H

#include <stdint.h>

typedef enum {
    UNDEF, IMP, ACC, IMM, ABS,
    X_IN_ABS, Y_IN_ABS,
    ABS_IND, ZP,
    X_IN_ZP, Y_IN_ZP,
    X_IN_ZP_IND, ZP_IND_Y_IN,
    REL
} AddressingMode;

typedef struct {
    const char* format;
    AddressingMode aMode;
    uint32_t operandCount;
} Mnemonic;

void opInitTable();

Mnemonic* opFindMnemonic(uint8_t opcode);

#endif
