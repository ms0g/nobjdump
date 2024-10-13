#pragma once

#include <string>
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
    REL
};

struct MnemonicData {
    std::string format;
    AddressingMode mode;
    int n;
};

class OpcodeTable {
public:
    OpcodeTable();

    [[nodiscard]] MnemonicData find(uint8_t opcode) const;

private:
    std::unordered_map<uint8_t, MnemonicData> mOpcodeToMnemonicList;
};

