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

void InstructionDecoder::fmtDisplay(const std::vector<uint8_t>& data, uint16_t index) const {
    std::cout << std::format("{:#x}:\t\t", index);

    for (int i = 0; i < data.size(); ++i) {
        std::cout << std::format("{:#x} ", data[i]);

        if ((i != 0) && i % 16 == 0) {
            std::cout << "\n";
            std::cout << std::format("{:#x}:\t\t", index + i);
        }
    }
}

void InstructionDecoder::disassemble() {

}
