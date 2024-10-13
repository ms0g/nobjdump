#pragma once

#include <string>
#include <unordered_map>

enum class Opcode : uint8_t {
    BRK = 0x00,
    CLC = 0x18,
    CLD = 0xD8,
    CLI = 0x58,
    CLV = 0xB8,
    DEX = 0xCA,
    DEY = 0x88,
    INX = 0xE8,
    INY = 0xC8,
    NOP = 0xEA,
    PHA = 0x48,
    PHP = 0x08,
    PLA = 0x68,
    PLP = 0x28,
    RTI = 0x40,
    RTS = 0x60,
    SEC = 0x38,
    SED = 0xF8,
    SEI = 0x78,
    TAX = 0xAA,
    TAY = 0xA8,
    TSX = 0xBA,
    TXA = 0x8A,
    TXS = 0x9A,
    TYA = 0x98,

    LDA_IMM = 0xA9,
    LDA_ABS = 0xAD,
    LDA_X_IND_ABS = 0xBD,
    LDA_Y_IND_ABS = 0xB9,
    LDA_ZP = 0xA5,
    LDA_X_IND_ZP = 0xB5,
    LDA_X_IND_ZP_INDIRECT = 0xA1,
    LDA_ZP_INDIRECT_Y_IND = 0xB1,

    LDX_IMM = 0xA2,
    LDX_ABS = 0xAE,
    LDX_Y_IND_ABS = 0xBE,
    LDX_ZP = 0xA6,
    LDX_Y_IND_ZP = 0xB6,

    LDY_IMM = 0xA0,
    LDY_ABS = 0xAC,
    LDY_X_IND_ABS = 0xBC,
    LDY_ZP = 0xA4,
    LDY_X_IND_ZP = 0xB4,

    STA_ABS = 0x8D,
    STA_X_IND_ABS = 0x9D,
    STA_Y_IND_ABS = 0x99,
    STA_ZP = 0x85,
    STA_X_IND_ZP = 0x95,
    STA_X_IND_ZP_INDIRECT = 0x81,
    STA_ZP_INDIRECT_Y_IND = 0x91,

    STX_ABS = 0x8E,
    STX_ZP = 0x86,
    STX_Y_IND_ZP = 0x96,

    STY_ABS = 0x8C,
    STY_ZP = 0x84,
    STY_X_IND_ZP = 0x94,

    ASL_ACC = 0x0A,
    ASL_ABS = 0x0E,
    ASL_X_IND_ABS = 0x1E,
    ASL_ZP = 0x06,
    ASL_X_IND_ZP = 0x16,

    LSR_ACC = 0x4A,
    LSR_ABS = 0x4E,
    LSR_X_IND_ABS = 0x5E,
    LSR_ZP = 0x46,
    LSR_X_IND_ZP = 0x56,

    ROL_ACC = 0x2A,
    ROL_ABS = 0x2E,
    ROL_X_IND_ABS = 0x3E,
    ROL_ZP = 0x26,
    ROL_X_IND_ZP = 0x36,

    ROR_ACC = 0x6A,
    ROR_ABS = 0x6E,
    ROR_X_IND_ABS = 0x7E,
    ROR_ZP = 0x66,
    ROR_X_IND_ZP = 0x76,

    AND_IMM = 0x29,
    AND_ABS = 0x2D,
    AND_X_IND_ABS = 0x3D,
    AND_Y_IND_ABS = 0x39,
    AND_ZP = 0x25,
    AND_X_IND_ZP = 0x35,
    AND_X_IND_ZP_INDIRECT = 0x21,
    AND_ZP_INDIRECT_Y_IND = 0x31,

    BIT_ABS = 0x2C,
    BIT_ZP = 0x24,

    EOR_IMM = 0x49,
    EOR_ABS = 0x4D,
    EOR_X_IND_ABS = 0x5D,
    EOR_Y_IND_ABS = 0x59,
    EOR_ZP = 0x45,
    EOR_X_IND_ZP = 0x55,
    EOR_X_IND_ZP_INDIRECT = 0x41,
    EOR_ZP_INDIRECT_Y_IND = 0x51,

    ORA_IMM = 0x09,
    ORA_ABS = 0x0D,
    ORA_X_IND_ABS = 0x1D,
    ORA_Y_IND_ABS = 0x19,
    ORA_ZP = 0x05,
    ORA_X_IND_ZP = 0x15,
    ORA_X_IND_ZP_INDIRECT = 0x01,
    ORA_ZP_INDIRECT_Y_IND = 0x11,

    ADC_IMM = 0x69,
    ADC_ABS = 0x6D,
    ADC_X_IND_ABS = 0x7D,
    ADC_Y_IND_ABS = 0x79,
    ADC_ZP = 0x65,
    ADC_X_IND_ZP = 0x75,
    ADC_X_IND_ZP_INDIRECT = 0x61,
    ADC_ZP_INDIRECT_Y_IND = 0x71,

    CMP_IMM = 0xC9,
    CMP_ABS = 0xCD,
    CMP_X_IND_ABS = 0xDD,
    CMP_Y_IND_ABS = 0xD9,
    CMP_ZP = 0xC5,
    CMP_X_IND_ZP = 0xD5,
    CMP_X_IND_ZP_INDIRECT = 0xC1,
    CMP_ZP_INDIRECT_Y_IND = 0xD1,

    CPX_IMM = 0xE0,
    CPX_ABS = 0xEC,
    CPX_ZP = 0xE4,

    CPY_IMM = 0xC0,
    CPY_ABS = 0xCC,
    CPY_ZP = 0xC4,

    SBC_IMM = 0xE9,
    SBC_ABS = 0xED,
    SBC_X_IND_ABS = 0xFD,
    SBC_Y_IND_ABS = 0xF9,
    SBC_ZP = 0xE5,
    SBC_X_IND_ZP = 0xF5,
    SBC_X_IND_ZP_INDIRECT = 0xE1,
    SBC_ZP_INDIRECT_Y_IND = 0xF1,

    DEC_ABS = 0xCE,
    DEC_X_IND_ABS = 0xDE,
    DEC_ZP = 0xC6,
    DEC_X_IND_ZP = 0xD6,

    INC_ABS = 0xEE,
    INC_X_IND_ABS = 0xFE,
    INC_ZP = 0xE6,
    INC_X_IND_ZP = 0xF6,

    JMP_ABS = 0x4C,
    JMP_INDIRECT = 0x6C,

    JSR_ABS = 0x20,

    BCC = 0x90,
    BCS = 0xB0,
    BEQ = 0xF0,
    BMI = 0x30,
    BNE = 0xD0,
    BPL = 0x10,
    BVC = 0x50,
    BVS = 0x70
};

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

struct OpcodeData {
    std::string format;
    AddressingMode mode;
};

class OpcodeTable {
public:
    OpcodeTable();

    [[nodiscard]] OpcodeData find(uint8_t opcode) const;

private:
    std::unordered_map<uint8_t, OpcodeData> mOpcodeToMnemonicList;
};

