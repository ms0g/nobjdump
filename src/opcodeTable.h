#pragma once

#include <cstdint>

enum class AddressingMode {
    UNDEF, IMP, ACC, IMM, ABS,
    X_IN_ABS, Y_IN_ABS,
    ABS_IND, ZP,
    X_IN_ZP, Y_IN_ZP,
    X_IN_ZP_IND, ZP_IND_Y_IN,
    REL
};

struct Mnemonic {
    const char* format;
    AddressingMode mode;
    uint32_t operandCount;
};

class OpcodeTable {
public:
    OpcodeTable();

    [[nodiscard]] const Mnemonic& find(uint8_t opcode) const;

private:
    Mnemonic mMnemonicFromOpcode[256]{};
};

