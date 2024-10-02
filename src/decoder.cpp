#include "decoder.h"
#include <iostream>
#include <stdexcept>
#include <format>

#define MAGIC0 0x4E
#define MAGIC1 0x45
#define MAGIC2 0x53
#define MAGIC3 0x1A

#define INES_HEADER_SIZE 0x10
#define PRG_ROM_SIZE 0x4000
#define CHR_ROM_SIZE 0x2000

InstructionDecoder::InstructionDecoder(const std::string& filename) {
    mRomFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    try {
        mRomFile.open(filename, std::ios::in | std::ios::binary);
        mHeader.resize(INES_HEADER_SIZE);
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

        mRomFile.seekg(mPrgData.data.size());
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
            break;
        case Option::PRG:
            displayPRG();
            break;
        case Option::CHR:
            displayCHR();
            break;
    }

//    for (auto const &op: m_data) {
//        switch (static_cast<Opcode>(op)) {
//            case Opcode::RTI:
//                std::cout << "RTI" << "\t";
//                break;
//            case Opcode::RTS:
//                std::cout << "RTS" << "\t";
//                break;
//            case Opcode::BRK:
//                std::cout << "BRK" << "\t";
//                break;
//            case Opcode::PHP:
//                std::cout << "PHP" << "\t";
//                break;
//            case Opcode::PLP:
//                std::cout << "PLP" << "\t";
//                break;
//            case Opcode::PHA:
//                std::cout << "PHA" << "\t";
//                break;
//            case Opcode::PLA:
//                std::cout << "PLA" << "\t";
//                break;
//            case Opcode::DEY:
//                std::cout << "DEY" << "\t";
//                break;
//            case Opcode::TAY:
//                std::cout << "TAY" << "\t";
//                break;
//            case Opcode::INY:
//                std::cout << "INY" << "\t";
//                break;
//            case Opcode::INX:
//                std::cout << "INX" << "\t";
//                break;
//            case Opcode::BCS:
//                std::cout << "BCS" << "\t";
//                break;
//            case Opcode::BCC:
//                std::cout << "BCC" << "\t";
//                break;
//            case Opcode::BEQ:
//                std::cout << "BEQ" << "\t";
//                break;
//            case Opcode::BNE:
//                std::cout << "BNE" << "\t";
//                break;
//            case Opcode::BPL:
//                std::cout << "BPL" << "\t";
//                break;
//            case Opcode::BMI:
//                std::cout << "BMI" << "\t";
//                break;
//            case Opcode::BVC:
//                std::cout << "BVC" << "\t";
//                break;
//            case Opcode::BVS:
//                std::cout << "BVS" << "\t";
//                break;
//            case Opcode::SEC:
//                std::cout << "SEC" << "\t";
//                break;
//            case Opcode::SEI:
//                std::cout << "SEI" << "\t";
//                break;
//            case Opcode::SED:
//                std::cout << "SED" << "\t";
//                break;
//            case Opcode::CLD:
//                std::cout << "CLD" << "\t";
//                break;
//            case Opcode::CLV:
//                std::cout << "CLV" << "\t";
//                break;
//            case Opcode::CLC:
//                std::cout << "CLC" << "\t";
//                break;
//            case Opcode::CLI:
//                std::cout << "CLI" << "\t";
//                break;
//            default:
//                std::cout << "Unknown OPCODE" << "\t";
//        }
//    }


}

void InstructionDecoder::displayHeader() {
    for (const auto& data: mHeader) {
        std::cout << std::format("{:#x} ", data);
    }
}

void InstructionDecoder::displayPRG() {
    for (const auto& data: mPrgData.data) {
        std::cout << std::format("{:#x} ", data);
    }
}

void InstructionDecoder::displayCHR() {
    for (const auto& data: mChrData.data) {
        std::cout << std::format("{:#x} ", data);
    }
}

void InstructionDecoder::disassemble() {

}
