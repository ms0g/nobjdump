#include "decoder.h"
#include <iostream>
#include <stdexcept>
#include <format>

#define MAGIC0 0x4E
#define MAGIC1 0x45
#define MAGIC2 0x53
#define MAGIC3 0x1A

#define INES_HEADER_SIZE 0x10
#define PRG_ROM_SIZE     0x4000
#define CHR_ROM_SIZE     0x2000

InstructionDecoder::InstructionDecoder(const std::string& filename) {
    mRomFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    try {
        mRomFile.open(filename, std::ios::in | std::ios::binary);
        mRomFile.read(reinterpret_cast<char*>(mHeader.data()), mHeader.size());

        if (mHeader[0] != MAGIC0 || mHeader[1] != MAGIC1 ||
            mHeader[2] != MAGIC2 || mHeader[3] != MAGIC3) {
            throw std::invalid_argument("Invalid NES rom file");
        }

        mPrgData.size = mHeader[4];
        if (!mPrgData.size) {
            throw std::invalid_argument("No PRG ROM");
        }

        mPrgData.data.resize(PRG_ROM_SIZE * mPrgData.size);
        mPrgData.index = INES_HEADER_SIZE;

        mChrData.size = mHeader[5];
        mChrData.data.resize(CHR_ROM_SIZE * mChrData.size);
        mChrData.index = INES_HEADER_SIZE + mPrgData.data.size();

        mRomFile.seekg(mPrgData.index);
        mRomFile.read(reinterpret_cast<char*>(mPrgData.data.data()), mPrgData.data.size());

        mRomFile.seekg(mChrData.index);
        mRomFile.read(reinterpret_cast<char*>(mChrData.data.data()), mChrData.data.size());
    } catch (std::ifstream::failure& e) {
        std::cerr << "Exception opening/reading ROM file: " << e.what() << "\t";
        exit(EXIT_FAILURE);
    }
}

InstructionDecoder::~InstructionDecoder() {
    mRomFile.close();
}

void InstructionDecoder::decode(Option opt) {
    switch (opt) {
        case Option::HEADER:
            displayHeader();
            break;
        case Option::DISASSEMBLE:
            disassemble();
            break;
        case Option::PRG:
            displayPRG();
            break;
        case Option::CHR:
            displayCHR();
            break;
    }
}

void InstructionDecoder::displayHeader() {
    fmtDisplay(mHeader, 0);
}

void InstructionDecoder::displayPRG() {
    fmtDisplay(mPrgData.data, mPrgData.index);
}

void InstructionDecoder::displayCHR() {
    fmtDisplay(mChrData.data, mChrData.index);
}

void InstructionDecoder::disassemble() {
    for (const auto& op: mPrgData.data) {
        switch (static_cast<Opcode>(op)) {
            case Opcode::RTI:
                std::cout << "RTI" << "\t";
                break;
            case Opcode::RTS:
                std::cout << "RTS" << "\t";
                break;
            case Opcode::BRK:
                std::cout << "BRK" << "\t";
                break;
            case Opcode::PHP:
                std::cout << "PHP" << "\t";
                break;
            case Opcode::PLP:
                std::cout << "PLP" << "\t";
                break;
            case Opcode::PHA:
                std::cout << "PHA" << "\t";
                break;
            case Opcode::PLA:
                std::cout << "PLA" << "\t";
                break;
            case Opcode::DEY:
                std::cout << "DEY" << "\t";
                break;
            case Opcode::TAY:
                std::cout << "TAY" << "\t";
                break;
            case Opcode::INY:
                std::cout << "INY" << "\t";
                break;
            case Opcode::INX:
                std::cout << "INX" << "\t";
                break;
            case Opcode::BCS:
                std::cout << "BCS" << "\t";
                break;
            case Opcode::BCC:
                std::cout << "BCC" << "\t";
                break;
            case Opcode::BEQ:
                std::cout << "BEQ" << "\t";
                break;
            case Opcode::BNE:
                std::cout << "BNE" << "\t";
                break;
            case Opcode::BPL:
                std::cout << "BPL" << "\t";
                break;
            case Opcode::BMI:
                std::cout << "BMI" << "\t";
                break;
            case Opcode::BVC:
                std::cout << "BVC" << "\t";
                break;
            case Opcode::BVS:
                std::cout << "BVS" << "\t";
                break;
            case Opcode::SEC:
                std::cout << "SEC" << "\t";
                break;
            case Opcode::SEI:
                std::cout << "SEI" << "\t";
                break;
            case Opcode::SED:
                std::cout << "SED" << "\t";
                break;
            case Opcode::CLD:
                std::cout << "CLD" << "\t";
                break;
            case Opcode::CLV:
                std::cout << "CLV" << "\t";
                break;
            case Opcode::CLC:
                std::cout << "CLC" << "\t";
                break;
            case Opcode::CLI:
                std::cout << "CLI" << "\t";
                break;
            case Opcode::DEX:
                break;
            case Opcode::NOP:
                break;
            case Opcode::TAX:
                break;
            case Opcode::TSX:
                break;
            case Opcode::TXA:
                break;
            case Opcode::TXS:
                break;
            case Opcode::TYA:
                break;
            case Opcode::LDA_IMM:
                break;
            case Opcode::LDA_ABS:
                break;
            case Opcode::LDA_X_IND_ABS:
                break;
            case Opcode::LDA_Y_IND_ABS:
                break;
            case Opcode::LDA_ZP:
                break;
            case Opcode::LDA_X_IND_ZP:
                break;
            case Opcode::LDA_X_IND_ZP_INDIRECT:
                break;
            case Opcode::LDA_ZP_INDIRECT_Y_IND:
                break;
            case Opcode::LDX_IMM:
                break;
            case Opcode::LDX_ABS:
                break;
            case Opcode::LDX_Y_IND_ABS:
                break;
            case Opcode::LDX_ZP:
                break;
            case Opcode::LDX_Y_IND_ZP:
                break;
            case Opcode::LDY_IMM:
                break;
            case Opcode::LDY_ABS:
                break;
            case Opcode::LDY_X_IND_ABS:
                break;
            case Opcode::LDY_ZP:
                break;
            case Opcode::LDY_X_IND_ZP:
                break;
            case Opcode::STA_ABS:
                break;
            case Opcode::STA_X_IND_ABS:
                break;
            case Opcode::STA_Y_IND_ABS:
                break;
            case Opcode::STA_ZP:
                break;
            case Opcode::STA_X_IND_ZP:
                break;
            case Opcode::STA_X_IND_ZP_INDIRECT:
                break;
            case Opcode::STA_ZP_INDIRECT_Y_IND:
                break;
            case Opcode::STX_ABS:
                break;
            case Opcode::STX_ZP:
                break;
            case Opcode::STX_Y_IND_ZP:
                break;
            case Opcode::STY_ABS:
                break;
            case Opcode::STY_ZP:
                break;
            case Opcode::STY_X_IND_ZP:
                break;
            case Opcode::ASL_ACC:
                break;
            case Opcode::ASL_ABS:
                break;
            case Opcode::ASL_X_IND_ABS:
                break;
            case Opcode::ASL_ZP:
                break;
            case Opcode::ASL_X_IND_ZP:
                break;
            case Opcode::LSR_ACC:
                break;
            case Opcode::LSR_ABS:
                break;
            case Opcode::LSR_X_IND_ABS:
                break;
            case Opcode::LSR_ZP:
                break;
            case Opcode::LSR_X_IND_ZP:
                break;
            case Opcode::ROL_ACC:
                break;
            case Opcode::ROL_ABS:
                break;
            case Opcode::ROL_X_IND_ABS:
                break;
            case Opcode::ROL_ZP:
                break;
            case Opcode::ROL_X_IND_ZP:
                break;
            case Opcode::ROR_ACC:
                break;
            case Opcode::ROR_ABS:
                break;
            case Opcode::ROR_X_IND_ABS:
                break;
            case Opcode::ROR_ZP:
                break;
            case Opcode::ROR_X_IND_ZP:
                break;
            case Opcode::AND_IMM:
                break;
            case Opcode::AND_ABS:
                break;
            case Opcode::AND_X_IND_ABS:
                break;
            case Opcode::AND_Y_IND_ABS:
                break;
            case Opcode::AND_ZP:
                break;
            case Opcode::AND_X_IND_ZP:
                break;
            case Opcode::AND_X_IND_ZP_INDIRECT:
                break;
            case Opcode::AND_ZP_INDIRECT_Y_IND:
                break;
            case Opcode::BIT_ABS:
                break;
            case Opcode::BIT_ZP:
                break;
            case Opcode::EOR_IMM:
                break;
            case Opcode::EOR_ABS:
                break;
            case Opcode::EOR_X_IND_ABS:
                break;
            case Opcode::EOR_Y_IND_ABS:
                break;
            case Opcode::EOR_ZP:
                break;
            case Opcode::EOR_X_IND_ZP:
                break;
            case Opcode::EOR_X_IND_ZP_INDIRECT:
                break;
            case Opcode::EOR_ZP_INDIRECT_Y_IND:
                break;
            case Opcode::ORA_IMM:
                break;
            case Opcode::ORA_ABS:
                break;
            case Opcode::ORA_X_IND_ABS:
                break;
            case Opcode::ORA_Y_IND_ABS:
                break;
            case Opcode::ORA_ZP:
                break;
            case Opcode::ORA_X_IND_ZP:
                break;
            case Opcode::ORA_X_IND_ZP_INDIRECT:
                break;
            case Opcode::ORA_ZP_INDIRECT_Y_IND:
                break;
            case Opcode::ADC_IMM:
                break;
            case Opcode::ADC_ABS:
                break;
            case Opcode::ADC_X_IND_ABS:
                break;
            case Opcode::ADC_Y_IND_ABS:
                break;
            case Opcode::ADC_ZP:
                break;
            case Opcode::ADC_X_IND_ZP:
                break;
            case Opcode::ADC_X_IND_ZP_INDIRECT:
                break;
            case Opcode::ADC_ZP_INDIRECT_Y_IND:
                break;
            case Opcode::CMP_IMM:
                break;
            case Opcode::CMP_ABS:
                break;
            case Opcode::CMP_X_IND_ABS:
                break;
            case Opcode::CMP_Y_IND_ABS:
                break;
            case Opcode::CMP_ZP:
                break;
            case Opcode::CMP_X_IND_ZP:
                break;
            case Opcode::CMP_X_IND_ZP_INDIRECT:
                break;
            case Opcode::CMP_ZP_INDIRECT_Y_IND:
                break;
            case Opcode::CPX_IMM:
                break;
            case Opcode::CPX_ABS:
                break;
            case Opcode::CPX_ZP:
                break;
            case Opcode::CPY_IMM:
                break;
            case Opcode::CPY_ABS:
                break;
            case Opcode::CPY_ZP:
                break;
            case Opcode::SBC_IMM:
                break;
            case Opcode::SBC_ABS:
                break;
            case Opcode::SBC_X_IND_ABS:
                break;
            case Opcode::SBC_Y_IND_ABS:
                break;
            case Opcode::SBC_ZP:
                break;
            case Opcode::SBC_X_IND_ZP:
                break;
            case Opcode::SBC_X_IND_ZP_INDIRECT:
                break;
            case Opcode::SBC_ZP_INDIRECT_Y_IND:
                break;
            case Opcode::DEC_ABS:
                break;
            case Opcode::DEC_X_IND_ABS:
                break;
            case Opcode::DEC_ZP:
                break;
            case Opcode::DEC_X_IND_ZP:
                break;
            case Opcode::INC_ABS:
                break;
            case Opcode::INC_X_IND_ABS:
                break;
            case Opcode::INC_ZP:
                break;
            case Opcode::INC_X_IND_ZP:
                break;
            case Opcode::JMP_ABS:
                break;
            case Opcode::JMP_INDIRECT:
                break;
            case Opcode::JSR_ABS:
                break;
        }
    }
}

template<typename T>
void InstructionDecoder::fmtDisplay(const T& data, uint16_t index) {
    for (int i = 0; i < data.size() / 16; i += 16) {
        int k = 0;
        char ascii[16];

        for (int j = i; j < 16 + i; ++j) {
            ascii[k++] = isprint(data[j]) ? data[j] : '.';
        }

        std::cout << std::format("{:06x}:\t{:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} "
                                 "{:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x}"
                                 "  {}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}\n", index + i,
                                 data[i], data[i + 1], data[i + 2], data[i + 3], data[i + 4], data[i + 5], data[i + 6],
                                 data[i + 7], data[i + 8], data[i + 9], data[i + 10], data[i + 11], data[i + 12],
                                 data[i + 13], data[i + 14], data[i + 15], ascii[0], ascii[1], ascii[2], ascii[3],
                                 ascii[4], ascii[5], ascii[6], ascii[7], ascii[8], ascii[9], ascii[10], ascii[11],
                                 ascii[12], ascii[13], ascii[14], ascii[15]);
    }
}