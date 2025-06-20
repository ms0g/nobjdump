#include "opcode.h"
#include <string.h>

#define IMM(OPCODE) OPCODE " #$%s"
#define ABS(OPCODE) OPCODE " $%s"
#define ACC(OPCODE) OPCODE " A"
#define ZP(OPCODE) ABS(OPCODE)
#define REL(OPCODE) ABS(OPCODE)
#define X_IN_ABS(OPCODE) OPCODE " $%s,X"
#define Y_IN_ABS(OPCODE) OPCODE " $%s,Y"
#define X_IN_ZP(OPCODE) X_IN_ABS(OPCODE)
#define Y_IN_ZP(OPCODE) Y_IN_ABS(OPCODE)
#define X_IN_ZP_IND(OPCODE) OPCODE " ($%s,X)"
#define ZP_IND_Y_IN(OPCODE) OPCODE " ($%s),Y"

static Mnemonic opcodeTable[256];

void opInitTable() {
    memset(opcodeTable, 0, sizeof(Mnemonic) * 256);

    opcodeTable[0x00] = (Mnemonic){"BRK", IMP, 0};
    opcodeTable[0x18] = (Mnemonic){"CLC", IMP, 0};
    opcodeTable[0xD8] = (Mnemonic){"CLD", IMP, 0};
    opcodeTable[0x58] = (Mnemonic){"CLI", IMP, 0};
    opcodeTable[0xB8] = (Mnemonic){"CLV", IMP, 0};
    opcodeTable[0xCA] = (Mnemonic){"DEX", IMP, 0};
    opcodeTable[0x88] = (Mnemonic){"DEY", IMP, 0};
    opcodeTable[0xE8] = (Mnemonic){"INX", IMP, 0};
    opcodeTable[0xC8] = (Mnemonic){"INY", IMP, 0};
    opcodeTable[0xEA] = (Mnemonic){"NOP", IMP, 0};
    opcodeTable[0x48] = (Mnemonic){"PHA", IMP, 0};
    opcodeTable[0x08] = (Mnemonic){"PHP", IMP, 0};
    opcodeTable[0x68] = (Mnemonic){"PLA", IMP, 0};
    opcodeTable[0x28] = (Mnemonic){"PLP", IMP, 0};
    opcodeTable[0x40] = (Mnemonic){"RTI", IMP, 0};
    opcodeTable[0x60] = (Mnemonic){"RTS", IMP, 0};
    opcodeTable[0x38] = (Mnemonic){"SEC", IMP, 0};
    opcodeTable[0xF8] = (Mnemonic){"SED", IMP, 0};
    opcodeTable[0x78] = (Mnemonic){"SEI", IMP, 0};
    opcodeTable[0xAA] = (Mnemonic){"TAX", IMP, 0};
    opcodeTable[0xA8] = (Mnemonic){"TAY", IMP, 0};
    opcodeTable[0xBA] = (Mnemonic){"TSX", IMP, 0};
    opcodeTable[0x8A] = (Mnemonic){"TXA", IMP, 0};
    opcodeTable[0x9A] = (Mnemonic){"TXS", IMP, 0};
    opcodeTable[0x98] = (Mnemonic){"TYA", IMP, 0};
    opcodeTable[0xA9] = (Mnemonic){IMM("LDA"), IMM, 1};
    opcodeTable[0xAD] = (Mnemonic){ABS("LDA"), ABS, 2};
    opcodeTable[0xBD] = (Mnemonic){X_IN_ABS("LDA"), X_IN_ABS, 2};
    opcodeTable[0xB9] = (Mnemonic){Y_IN_ABS("LDA"), Y_IN_ABS, 2};
    opcodeTable[0xA5] = (Mnemonic){ZP("LDA"), ZP, 1};
    opcodeTable[0xB5] = (Mnemonic){X_IN_ZP("LDA"), X_IN_ZP, 1};
    opcodeTable[0xA1] = (Mnemonic){X_IN_ZP_IND("LDA"), X_IN_ZP_IND, 1};
    opcodeTable[0xB1] = (Mnemonic){ZP_IND_Y_IN("LDA"), ZP_IND_Y_IN, 1};
    opcodeTable[0xA2] = (Mnemonic){IMM("LDX"), IMM, 1};
    opcodeTable[0xAE] = (Mnemonic){ABS("LDX"), ABS, 2};
    opcodeTable[0xBE] = (Mnemonic){Y_IN_ABS("LDX"), Y_IN_ABS, 2};
    opcodeTable[0xA6] = (Mnemonic){ZP("LDX"), ZP, 1};
    opcodeTable[0xB6] = (Mnemonic){Y_IN_ZP("LDX"), Y_IN_ZP, 1};
    opcodeTable[0xA0] = (Mnemonic){IMM("LDY"), IMM, 1};
    opcodeTable[0xAC] = (Mnemonic){ABS("LDY"), ABS, 2};
    opcodeTable[0xBC] = (Mnemonic){X_IN_ABS("LDY"), X_IN_ABS, 2};
    opcodeTable[0xA4] = (Mnemonic){ZP("LDY"), ZP, 1};
    opcodeTable[0xB4] = (Mnemonic){X_IN_ZP("LDY"), X_IN_ZP, 1};
    opcodeTable[0x8D] = (Mnemonic){ABS("STA"), ABS, 2};
    opcodeTable[0x9D] = (Mnemonic){X_IN_ABS("STA"), X_IN_ABS, 2};
    opcodeTable[0x99] = (Mnemonic){Y_IN_ABS("STA"), Y_IN_ABS, 2};
    opcodeTable[0x85] = (Mnemonic){ZP("STA"), ZP, 1};
    opcodeTable[0x95] = (Mnemonic){X_IN_ZP("STA"), X_IN_ZP, 1};
    opcodeTable[0x81] = (Mnemonic){X_IN_ZP_IND("STA"), X_IN_ZP_IND, 1};
    opcodeTable[0x91] = (Mnemonic){ZP_IND_Y_IN("STA"), ZP_IND_Y_IN, 1};
    opcodeTable[0x8E] = (Mnemonic){ABS("STX"), ABS, 2};
    opcodeTable[0x86] = (Mnemonic){ZP("STX"), ZP, 1};
    opcodeTable[0x96] = (Mnemonic){Y_IN_ZP("STX"), Y_IN_ZP, 1};
    opcodeTable[0x8C] = (Mnemonic){ABS("STY"), ABS, 2};
    opcodeTable[0x84] = (Mnemonic){ZP("STY"), ZP, 1};
    opcodeTable[0x94] = (Mnemonic){X_IN_ZP("STY"), X_IN_ZP, 1};
    opcodeTable[0x0A] = (Mnemonic){ACC("ASL"), ACC};
    opcodeTable[0x0E] = (Mnemonic){ABS("ASL"), ABS, 2};
    opcodeTable[0x1E] = (Mnemonic){X_IN_ABS("ASL"), X_IN_ABS, 2};
    opcodeTable[0x06] = (Mnemonic){ZP("ASL"), ZP, 1};
    opcodeTable[0x16] = (Mnemonic){X_IN_ZP("ASL"), X_IN_ZP, 1};
    opcodeTable[0x4A] = (Mnemonic){ACC("LSR"), ACC};
    opcodeTable[0x4E] = (Mnemonic){ABS("LSR"), ABS, 2};
    opcodeTable[0x5E] = (Mnemonic){X_IN_ABS("LSR"), X_IN_ABS, 2};
    opcodeTable[0x46] = (Mnemonic){ZP("LSR"), ZP, 1};
    opcodeTable[0x56] = (Mnemonic){X_IN_ZP("LSR"), X_IN_ZP, 1};
    opcodeTable[0x2A] = (Mnemonic){ACC("ROL"), ACC};
    opcodeTable[0x2E] = (Mnemonic){ABS("ROL"), ABS, 2};
    opcodeTable[0x3E] = (Mnemonic){X_IN_ABS("ROL"), X_IN_ABS, 2};
    opcodeTable[0x26] = (Mnemonic){ZP("ROL"), ZP, 1};
    opcodeTable[0x36] = (Mnemonic){X_IN_ZP("ROL"), X_IN_ZP, 1};
    opcodeTable[0x6A] = (Mnemonic){ACC("ROR"), ACC};
    opcodeTable[0x6E] = (Mnemonic){ABS("ROR"), ABS, 2};
    opcodeTable[0x7E] = (Mnemonic){X_IN_ABS("ROR"), X_IN_ABS, 2};
    opcodeTable[0x66] = (Mnemonic){ZP("ROR"), ZP, 1};
    opcodeTable[0x76] = (Mnemonic){X_IN_ZP("ROR"), X_IN_ZP, 1};
    opcodeTable[0x29] = (Mnemonic){IMM("AND"), IMM, 1};
    opcodeTable[0x2D] = (Mnemonic){ABS("AND"), ABS, 2};
    opcodeTable[0x3D] = (Mnemonic){X_IN_ABS("AND"), X_IN_ABS, 2};
    opcodeTable[0x39] = (Mnemonic){Y_IN_ABS("AND"), Y_IN_ABS, 2};
    opcodeTable[0x25] = (Mnemonic){ZP("AND"), ZP, 1};
    opcodeTable[0x35] = (Mnemonic){X_IN_ZP("AND"), X_IN_ZP, 1};
    opcodeTable[0x21] = (Mnemonic){X_IN_ZP_IND("AND"), X_IN_ZP_IND, 1};
    opcodeTable[0x31] = (Mnemonic){ZP_IND_Y_IN("AND"), ZP_IND_Y_IN, 1};
    opcodeTable[0x2C] = (Mnemonic){ABS("BIT"), ABS, 2};
    opcodeTable[0x24] = (Mnemonic){ZP("BIT"), ZP, 1};
    opcodeTable[0x49] = (Mnemonic){IMM("EOR"), IMM, 1};
    opcodeTable[0x4D] = (Mnemonic){ABS("EOR"), ABS, 2};
    opcodeTable[0x5D] = (Mnemonic){X_IN_ABS("EOR"), X_IN_ABS, 2};
    opcodeTable[0x59] = (Mnemonic){Y_IN_ABS("EOR"), Y_IN_ABS, 2};
    opcodeTable[0x45] = (Mnemonic){ZP("EOR"), ZP, 1};
    opcodeTable[0x55] = (Mnemonic){X_IN_ZP("EOR"), X_IN_ZP, 1};
    opcodeTable[0x41] = (Mnemonic){X_IN_ZP_IND("EOR"), X_IN_ZP_IND, 1};
    opcodeTable[0x51] = (Mnemonic){ZP_IND_Y_IN("EOR"), ZP_IND_Y_IN, 1};
    opcodeTable[0x09] = (Mnemonic){IMM("ORA"), IMM, 1};
    opcodeTable[0x0D] = (Mnemonic){ABS("ORA"), ABS, 2};
    opcodeTable[0x1D] = (Mnemonic){X_IN_ABS("ORA"), X_IN_ABS, 2};
    opcodeTable[0x19] = (Mnemonic){Y_IN_ABS("ORA"), Y_IN_ABS, 2};
    opcodeTable[0x05] = (Mnemonic){ZP("ORA"), ZP, 1};
    opcodeTable[0x15] = (Mnemonic){X_IN_ZP("ORA"), X_IN_ZP, 1};
    opcodeTable[0x01] = (Mnemonic){X_IN_ZP_IND("ORA"), X_IN_ZP_IND, 1};
    opcodeTable[0x11] = (Mnemonic){ZP_IND_Y_IN("ORA"), ZP_IND_Y_IN, 1};
    opcodeTable[0x69] = (Mnemonic){IMM("ADC"), IMM, 1};
    opcodeTable[0x6D] = (Mnemonic){ABS("ADC"), ABS, 2};
    opcodeTable[0x7D] = (Mnemonic){X_IN_ABS("ADC"), X_IN_ABS, 2};
    opcodeTable[0x79] = (Mnemonic){Y_IN_ABS("ADC"), Y_IN_ABS, 2};
    opcodeTable[0x65] = (Mnemonic){ZP("ADC"), ZP, 1};
    opcodeTable[0x75] = (Mnemonic){X_IN_ZP("ADC"), X_IN_ZP, 1};
    opcodeTable[0x61] = (Mnemonic){X_IN_ZP_IND("ADC"), X_IN_ZP_IND, 1};
    opcodeTable[0x71] = (Mnemonic){ZP_IND_Y_IN("ADC"), ZP_IND_Y_IN, 1};
    opcodeTable[0xC9] = (Mnemonic){IMM("CMP"), IMM, 1};
    opcodeTable[0xCD] = (Mnemonic){ABS("CMP"), ABS, 2};
    opcodeTable[0xDD] = (Mnemonic){X_IN_ABS("CMP"), X_IN_ABS, 2};
    opcodeTable[0xD9] = (Mnemonic){Y_IN_ABS("CMP"), Y_IN_ABS, 2};
    opcodeTable[0xC5] = (Mnemonic){ZP("CMP"), ZP, 1};
    opcodeTable[0xD5] = (Mnemonic){X_IN_ZP("CMP"), X_IN_ZP, 1};
    opcodeTable[0xC1] = (Mnemonic){X_IN_ZP_IND("CMP"), X_IN_ZP_IND, 1};
    opcodeTable[0xD1] = (Mnemonic){ZP_IND_Y_IN("CMP"), ZP_IND_Y_IN, 1};
    opcodeTable[0xE0] = (Mnemonic){IMM("CPX"), IMM, 1};
    opcodeTable[0xEC] = (Mnemonic){ABS("CPX"), ABS, 2};
    opcodeTable[0xE4] = (Mnemonic){ZP("CPX"), ZP, 1};
    opcodeTable[0xC0] = (Mnemonic){IMM("CPY"), IMM, 1};
    opcodeTable[0xCC] = (Mnemonic){ABS("CPY"), ABS, 2};
    opcodeTable[0xC4] = (Mnemonic){ZP("CPY"), ZP, 1};
    opcodeTable[0xE9] = (Mnemonic){IMM("SBC"), IMM, 1};
    opcodeTable[0xED] = (Mnemonic){ABS("SBC"), ABS, 2};
    opcodeTable[0xFD] = (Mnemonic){X_IN_ABS("SBC"), X_IN_ABS, 2};
    opcodeTable[0xF9] = (Mnemonic){Y_IN_ABS("SBC"), Y_IN_ABS, 2};
    opcodeTable[0xE5] = (Mnemonic){ZP("SBC"), ZP, 1};
    opcodeTable[0xF5] = (Mnemonic){X_IN_ZP("SBC"), X_IN_ZP, 1};
    opcodeTable[0xE1] = (Mnemonic){X_IN_ZP_IND("SBC"), X_IN_ZP_IND, 1};
    opcodeTable[0xF1] = (Mnemonic){ZP_IND_Y_IN("SBC"), ZP_IND_Y_IN, 1};
    opcodeTable[0xCE] = (Mnemonic){ABS("DEC"), ABS, 2};
    opcodeTable[0xDE] = (Mnemonic){X_IN_ABS("DEC"), X_IN_ABS, 2};
    opcodeTable[0xC6] = (Mnemonic){ZP("DEC"), ZP, 1};
    opcodeTable[0xD6] = (Mnemonic){X_IN_ZP("DEC"), X_IN_ZP, 1};
    opcodeTable[0xEE] = (Mnemonic){ABS("INC"), ABS, 2};
    opcodeTable[0xFE] = (Mnemonic){X_IN_ABS("INC"), X_IN_ABS, 2};
    opcodeTable[0xE6] = (Mnemonic){ZP("INC"), ZP, 1};
    opcodeTable[0xF6] = (Mnemonic){X_IN_ZP("INC"), X_IN_ZP, 1};
    opcodeTable[0x4C] = (Mnemonic){ABS("JMP"), ABS, 2};
    opcodeTable[0x6C] = (Mnemonic){"JMP (${})", ABS_IND, 2};
    opcodeTable[0x20] = (Mnemonic){ABS("JSR"), ABS, 2};
    opcodeTable[0x90] = (Mnemonic){REL("BCC"), REL, 1};
    opcodeTable[0xB0] = (Mnemonic){REL("BCS"), REL, 1};
    opcodeTable[0xF0] = (Mnemonic){REL("BEQ"), REL, 1};
    opcodeTable[0x30] = (Mnemonic){REL("BMI"), REL, 1};
    opcodeTable[0xD0] = (Mnemonic){REL("BNE"), REL, 1};
    opcodeTable[0x10] = (Mnemonic){REL("BPL"), REL, 1};
    opcodeTable[0x50] = (Mnemonic){REL("BVC"), REL, 1};
    opcodeTable[0x70] = (Mnemonic){REL("BVS"), REL, 1};
}

Mnemonic* opFindMnemonic(const uint8_t opcode) {
    return &opcodeTable[opcode];
}
