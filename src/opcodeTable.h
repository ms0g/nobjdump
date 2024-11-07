#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

enum class AddressingMode {
    IMP,
    ACC,
    IMM,
    ABS,
    X_IN_ABS,
    Y_IN_ABS,
    ABS_IND,
    ZP,
    X_IN_ZP,
    Y_IN_ZP,
    X_IN_ZP_IND,
    ZP_IND_Y_IN,
    REL,
    UNDEF
};

struct Mnemonic {
    std::string format;
    AddressingMode mode;
    uint32_t operandCount;
};

class OpcodeTable {
public:
    OpcodeTable();

    [[nodiscard]] const Mnemonic& find(uint8_t opcode) const;

private:
    std::unordered_map<uint8_t, Mnemonic> mOpcodeToMnemonicList;
};

