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

InstructionDecoder::InstructionDecoder(const char* filename) {
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
    displayFormattedData(mHeader, 0);
}

void InstructionDecoder::displayPRG() {
    displayFormattedData(mPrgData.data, mPrgData.index);
}

void InstructionDecoder::displayCHR() {
    displayFormattedData(mChrData.data, mChrData.index);
}

void InstructionDecoder::disassemble() {
    for (int i = 0; i < mPrgData.data.size(); ++i) {
        if (i > mPrgData.data.size()) break;

        uint8_t opcode = mPrgData.data[i];
        Mnemonic mnemonic = mOpcodeTable.find(opcode);

        if (mnemonic.format == "UNDEFINED")
            continue;

        if (mnemonic.mode == AddressingMode::IMP || mnemonic.mode == AddressingMode::ACC) {
            std::cout << std::format("{:06X}:\t{:02X}\t\t\t{}\n", mPrgData.index++, opcode, mnemonic.format);
        } else {
            std::vector<uint8_t> operand;
            std::string strOPR, hexOPR;

            for (int j = 1; j <= mnemonic.operandCount; ++j) {
                operand.push_back(mPrgData.data[i + j]);
            }

            i += mnemonic.operandCount;

            for (auto& op: operand) {
                hexOPR += std::format("{:02X} ", op);
            }

            for (int j = operand.size() - 1; j >= 0; --j) {
                strOPR += std::format("{:02X}", operand[j]);
            }

            std::cout << std::format("{:06X}:\t{:02X} {}",
                                     mPrgData.index++,
                                     opcode,
                                     hexOPR);
            if (operand.size() > 1)
                std::cout << std::format("\t{}\n", std::vformat(mnemonic.format, std::make_format_args(strOPR)));
            else
                std::cout << std::format("\t\t{}\n", std::vformat(mnemonic.format, std::make_format_args(strOPR)));
        }
    }
}

template<typename T>
void InstructionDecoder::displayFormattedData(const T& data, uint16_t index) {
    for (int i = 0; i < data.size() / 16; i += 16) {
        int k = 0;
        char ascii[16];

        for (int j = i; j < 16 + i; ++j) {
            ascii[k++] = isprint(data[j]) ? data[j] : '.';
        }

        std::cout << std::format("{:06X}:\t{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} "
                                 "{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}"
                                 "  {}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}\n", index + i,
                                 data[i], data[i + 1], data[i + 2], data[i + 3], data[i + 4], data[i + 5], data[i + 6],
                                 data[i + 7], data[i + 8], data[i + 9], data[i + 10], data[i + 11], data[i + 12],
                                 data[i + 13], data[i + 14], data[i + 15], ascii[0], ascii[1], ascii[2], ascii[3],
                                 ascii[4], ascii[5], ascii[6], ascii[7], ascii[8], ascii[9], ascii[10], ascii[11],
                                 ascii[12], ascii[13], ascii[14], ascii[15]);
    }
}