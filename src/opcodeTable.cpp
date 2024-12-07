#include "opcodeTable.h"

#define IMM(OPCODE) OPCODE " #${}"
#define ABS(OPCODE) OPCODE " ${}"
#define ACC(OPCODE) OPCODE " A"
#define ZP(OPCODE) ABS(OPCODE)
#define REL(OPCODE) ABS(OPCODE)
#define X_IN_ABS(OPCODE) OPCODE " ${},X"
#define Y_IN_ABS(OPCODE) OPCODE " ${},Y"
#define X_IN_ZP(OPCODE) X_IN_ABS(OPCODE)
#define Y_IN_ZP(OPCODE) Y_IN_ABS(OPCODE)
#define X_IN_ZP_IND(OPCODE) OPCODE " (${},X)"
#define ZP_IND_Y_IN(OPCODE) OPCODE " (${}),Y"

OpcodeTable::OpcodeTable() {
    memset(mMnemonicFromOpcode, 0, sizeof(mMnemonicFromOpcode));

    mMnemonicFromOpcode[0x00] = {"BRK", AddressingMode::IMP};
    mMnemonicFromOpcode[0x18] = {"CLC", AddressingMode::IMP};
    mMnemonicFromOpcode[0xD8] = {"CLD", AddressingMode::IMP};
    mMnemonicFromOpcode[0x58] = {"CLI", AddressingMode::IMP};
    mMnemonicFromOpcode[0xB8] = {"CLV", AddressingMode::IMP};
    mMnemonicFromOpcode[0xCA] = {"DEX", AddressingMode::IMP};
    mMnemonicFromOpcode[0x88] = {"DEY", AddressingMode::IMP};
    mMnemonicFromOpcode[0xE8] = {"INX", AddressingMode::IMP};
    mMnemonicFromOpcode[0xC8] = {"INY", AddressingMode::IMP};
    mMnemonicFromOpcode[0xEA] = {"NOP", AddressingMode::IMP};
    mMnemonicFromOpcode[0x48] = {"PHA", AddressingMode::IMP};
    mMnemonicFromOpcode[0x08] = {"PHP", AddressingMode::IMP};
    mMnemonicFromOpcode[0x68] = {"PLA", AddressingMode::IMP};
    mMnemonicFromOpcode[0x28] = {"PLP", AddressingMode::IMP};
    mMnemonicFromOpcode[0x40] = {"RTI", AddressingMode::IMP};
    mMnemonicFromOpcode[0x60] = {"RTS", AddressingMode::IMP};
    mMnemonicFromOpcode[0x38] = {"SEC", AddressingMode::IMP};
    mMnemonicFromOpcode[0xF8] = {"SED", AddressingMode::IMP};
    mMnemonicFromOpcode[0x78] = {"SEI", AddressingMode::IMP};
    mMnemonicFromOpcode[0xAA] = {"TAX", AddressingMode::IMP};
    mMnemonicFromOpcode[0xA8] = {"TAY", AddressingMode::IMP};
    mMnemonicFromOpcode[0xBA] = {"TSX", AddressingMode::IMP};
    mMnemonicFromOpcode[0x8A] = {"TXA", AddressingMode::IMP};
    mMnemonicFromOpcode[0x9A] = {"TXS", AddressingMode::IMP};
    mMnemonicFromOpcode[0x98] = {"TYA", AddressingMode::IMP};
    mMnemonicFromOpcode[0xA9] = {IMM("LDA"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0xAD] = {ABS("LDA"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0xBD] = {X_IN_ABS("LDA"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0xB9] = {Y_IN_ABS("LDA"), AddressingMode::Y_IN_ABS, 2};
    mMnemonicFromOpcode[0xA5] = {ZP("LDA"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0xB5] = {X_IN_ZP("LDA"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0xA1] = {X_IN_ZP_IND("LDA"), AddressingMode::X_IN_ZP_IND, 1};
    mMnemonicFromOpcode[0xB1] = {ZP_IND_Y_IN("LDA"), AddressingMode::ZP_IND_Y_IN, 1};
    mMnemonicFromOpcode[0xA2] = {IMM("LDX"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0xAE] = {ABS("LDX"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0xBE] = {Y_IN_ABS("LDX"), AddressingMode::Y_IN_ABS, 2};
    mMnemonicFromOpcode[0xA6] = {ZP("LDX"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0xB6] = {Y_IN_ZP("LDX"), AddressingMode::Y_IN_ZP, 1};
    mMnemonicFromOpcode[0xA0] = {IMM("LDY"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0xAC] = {ABS("LDY"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0xBC] = {X_IN_ABS("LDY"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0xA4] = {ZP("LDY"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0xB4] = {X_IN_ZP("LDY"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x8D] = {ABS("STA"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x9D] = {X_IN_ABS("STA"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0x99] = {Y_IN_ABS("STA"), AddressingMode::Y_IN_ABS, 2};
    mMnemonicFromOpcode[0x85] = {ZP("STA"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x95] = {X_IN_ZP("STA"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x81] = {X_IN_ZP_IND("STA"), AddressingMode::X_IN_ZP_IND, 1};
    mMnemonicFromOpcode[0x91] = {ZP_IND_Y_IN("STA"), AddressingMode::ZP_IND_Y_IN, 1};
    mMnemonicFromOpcode[0x8E] = {ABS("STX"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x86] = {ZP("STX"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x96] = {Y_IN_ZP("STX"), AddressingMode::Y_IN_ZP, 1};
    mMnemonicFromOpcode[0x8C] = {ABS("STY"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x84] = {ZP("STY"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x94] = {X_IN_ZP("STY"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x0A] = {ACC("ASL"), AddressingMode::ACC};
    mMnemonicFromOpcode[0x0E] = {ABS("ASL"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x1E] = {X_IN_ABS("ASL"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0x06] = {ZP("ASL"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x16] = {X_IN_ZP("ASL"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x4A] = {ACC("LSR"), AddressingMode::ACC};
    mMnemonicFromOpcode[0x4E] = {ABS("LSR"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x5E] = {X_IN_ABS("LSR"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0x46] = {ZP("LSR"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x56] = {X_IN_ZP("LSR"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x2A] = {ACC("ROL"), AddressingMode::ACC};
    mMnemonicFromOpcode[0x2E] = {ABS("ROL"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x3E] = {X_IN_ABS("ROL"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0x26] = {ZP("ROL"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x36] = {X_IN_ZP("ROL"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x6A] = {ACC("ROR"), AddressingMode::ACC};
    mMnemonicFromOpcode[0x6E] = {ABS("ROR"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x7E] = {X_IN_ABS("ROR"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0x66] = {ZP("ROR"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x76] = {X_IN_ZP("ROR"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x29] = {IMM("AND"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0x2D] = {ABS("AND"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x3D] = {X_IN_ABS("AND"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0x39] = {Y_IN_ABS("AND"), AddressingMode::Y_IN_ABS, 2};
    mMnemonicFromOpcode[0x25] = {ZP("AND"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x35] = {X_IN_ZP("AND"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x21] = {X_IN_ZP_IND("AND"), AddressingMode::X_IN_ZP_IND, 1};
    mMnemonicFromOpcode[0x31] = {ZP_IND_Y_IN("AND"), AddressingMode::ZP_IND_Y_IN, 1};
    mMnemonicFromOpcode[0x2C] = {ABS("BIT"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x24] = {ZP("BIT"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x49] = {IMM("EOR"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0x4D] = {ABS("EOR"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x5D] = {X_IN_ABS("EOR"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0x59] = {Y_IN_ABS("EOR"), AddressingMode::Y_IN_ABS, 2};
    mMnemonicFromOpcode[0x45] = {ZP("EOR"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x55] = {X_IN_ZP("EOR"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x41] = {X_IN_ZP_IND("EOR"), AddressingMode::X_IN_ZP_IND, 1};
    mMnemonicFromOpcode[0x51] = {ZP_IND_Y_IN("EOR"), AddressingMode::ZP_IND_Y_IN, 1};
    mMnemonicFromOpcode[0x09] = {IMM("ORA"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0x0D] = {ABS("ORA"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x1D] = {X_IN_ABS("ORA"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0x19] = {Y_IN_ABS("ORA"), AddressingMode::Y_IN_ABS, 2};
    mMnemonicFromOpcode[0x05] = {ZP("ORA"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x15] = {X_IN_ZP("ORA"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x01] = {X_IN_ZP_IND("ORA"), AddressingMode::X_IN_ZP_IND, 1};
    mMnemonicFromOpcode[0x11] = {ZP_IND_Y_IN("ORA"), AddressingMode::ZP_IND_Y_IN, 1};
    mMnemonicFromOpcode[0x69] = {IMM("ADC"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0x6D] = {ABS("ADC"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x7D] = {X_IN_ABS("ADC"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0x79] = {Y_IN_ABS("ADC"), AddressingMode::Y_IN_ABS, 2};
    mMnemonicFromOpcode[0x65] = {ZP("ADC"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0x75] = {X_IN_ZP("ADC"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x61] = {X_IN_ZP_IND("ADC"), AddressingMode::X_IN_ZP_IND, 1};
    mMnemonicFromOpcode[0x71] = {ZP_IND_Y_IN("ADC"), AddressingMode::ZP_IND_Y_IN, 1};
    mMnemonicFromOpcode[0xC9] = {IMM("CMP"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0xCD] = {ABS("CMP"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0xDD] = {X_IN_ABS("CMP"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0xD9] = {Y_IN_ABS("CMP"), AddressingMode::Y_IN_ABS, 2};
    mMnemonicFromOpcode[0xC5] = {ZP("CMP"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0xD5] = {X_IN_ZP("CMP"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0xC1] = {X_IN_ZP_IND("CMP"), AddressingMode::X_IN_ZP_IND, 1};
    mMnemonicFromOpcode[0xD1] = {ZP_IND_Y_IN("CMP"), AddressingMode::ZP_IND_Y_IN, 1};
    mMnemonicFromOpcode[0xE0] = {IMM("CPX"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0xEC] = {ABS("CPX"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0xE4] = {ZP("CPX"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0xC0] = {IMM("CPY"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0xCC] = {ABS("CPY"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0xC4] = {ZP("CPY"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0xE9] = {IMM("SBC"), AddressingMode::IMM, 1};
    mMnemonicFromOpcode[0xED] = {ABS("SBC"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0xFD] = {X_IN_ABS("SBC"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0xF9] = {Y_IN_ABS("SBC"), AddressingMode::Y_IN_ABS, 2};
    mMnemonicFromOpcode[0xE5] = {ZP("SBC"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0xF5] = {X_IN_ZP("SBC"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0xE1] = {X_IN_ZP_IND("SBC"), AddressingMode::X_IN_ZP_IND, 1};
    mMnemonicFromOpcode[0xF1] = {ZP_IND_Y_IN("SBC"), AddressingMode::ZP_IND_Y_IN, 1};
    mMnemonicFromOpcode[0xCE] = {ABS("DEC"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0xDE] = {X_IN_ABS("DEC"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0xC6] = {ZP("DEC"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0xD6] = {X_IN_ZP("DEC"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0xEE] = {ABS("INC"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0xFE] = {X_IN_ABS("INC"), AddressingMode::X_IN_ABS, 2};
    mMnemonicFromOpcode[0xE6] = {ZP("INC"), AddressingMode::ZP, 1};
    mMnemonicFromOpcode[0xF6] = {X_IN_ZP("INC"), AddressingMode::X_IN_ZP, 1};
    mMnemonicFromOpcode[0x4C] = {ABS("JMP"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x6C] = {"JMP (${})", AddressingMode::ABS_IND, 2};
    mMnemonicFromOpcode[0x20] = {ABS("JSR"), AddressingMode::ABS, 2};
    mMnemonicFromOpcode[0x90] = {REL("BCC"), AddressingMode::REL, 1};
    mMnemonicFromOpcode[0xB0] = {REL("BCS"), AddressingMode::REL, 1};
    mMnemonicFromOpcode[0xF0] = {REL("BEQ"), AddressingMode::REL, 1};
    mMnemonicFromOpcode[0x30] = {REL("BMI"), AddressingMode::REL, 1};
    mMnemonicFromOpcode[0xD0] = {REL("BNE"), AddressingMode::REL, 1};
    mMnemonicFromOpcode[0x10] = {REL("BPL"), AddressingMode::REL, 1};
    mMnemonicFromOpcode[0x50] = {REL("BVC"), AddressingMode::REL, 1};
    mMnemonicFromOpcode[0x70] = {REL("BVS"), AddressingMode::REL, 1};
}

const Mnemonic& OpcodeTable::find(uint8_t opcode) const {
    return mMnemonicFromOpcode[opcode];
}
