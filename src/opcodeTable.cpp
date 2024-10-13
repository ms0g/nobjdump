#include "opcodeTable.h"

OpcodeTable::OpcodeTable() {
    mOpcodeToMnemonicList = {
            {0x00, OpcodeData{"BRK", AddressingMode::IMP}},
            {0x18, OpcodeData{"CLC", AddressingMode::IMP}},
            {0xD8, OpcodeData{"CLD", AddressingMode::IMP}},
            {0x58, OpcodeData{"CLI", AddressingMode::IMP}},
            {0xB8, OpcodeData{"CLV", AddressingMode::IMP}},
            {0xCA, OpcodeData{"DEX", AddressingMode::IMP}},
            {0x88, OpcodeData{"DEY", AddressingMode::IMP}},
            {0xE8, OpcodeData{"INX", AddressingMode::IMP}},
            {0xC8, OpcodeData{"INY", AddressingMode::IMP}},
            {0xEA, OpcodeData{"NOP", AddressingMode::IMP}},
            {0x48, OpcodeData{"PHA", AddressingMode::IMP}},
            {0x08, OpcodeData{"PHP", AddressingMode::IMP}},
            {0x68, OpcodeData{"PLA", AddressingMode::IMP}},
            {0x28, OpcodeData{"PLP", AddressingMode::IMP}},
            {0x40, OpcodeData{"RTI", AddressingMode::IMP}},
            {0x60, OpcodeData{"RTS", AddressingMode::IMP}},
            {0x38, OpcodeData{"SEC", AddressingMode::IMP}},
            {0xF8, OpcodeData{"SED", AddressingMode::IMP}},
            {0x78, OpcodeData{"SEI", AddressingMode::IMP}},
            {0xAA, OpcodeData{"TAX", AddressingMode::IMP}},
            {0xA8, OpcodeData{"TAY", AddressingMode::IMP}},
            {0xBA, OpcodeData{"TSX", AddressingMode::IMP}},
            {0x8A, OpcodeData{"TXA", AddressingMode::IMP}},
            {0x9A, OpcodeData{"TXS", AddressingMode::IMP}},
            {0x98, OpcodeData{"TYA", AddressingMode::IMP}},

            {0xA9, OpcodeData{"LDA #${:02x}", AddressingMode::IMM}},
            {0xAD, OpcodeData{"LDA ${:02x}", AddressingMode::ABS}},
            {0xBD, OpcodeData{"LDA ${:02x},X", AddressingMode::X_IN_ABS}},
            {0xB9, OpcodeData{"LDA ${:02x},Y", AddressingMode::Y_IN_ABS}},
            {0xA5, OpcodeData{"LDA ${:02x}", AddressingMode::ZP}},
            {0xB5, OpcodeData{"LDA ${:02x},X", AddressingMode::X_IN_ZP}},
            {0xA1, OpcodeData{"LDA (${:02x},X)", AddressingMode::X_IN_ZP_IND}},
            {0xB1, OpcodeData{"LDA (${:02x}),Y", AddressingMode::ZP_IND_Y_IN}},

    };

}

OpcodeData OpcodeTable::find(uint8_t opcode) const {
    return mOpcodeToMnemonicList.find(opcode)->second;
}
