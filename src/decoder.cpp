#include "decoder.h"
#include <iostream>
#include <stdexcept>
#include <format>

InstructionDecoder::InstructionDecoder(const char* filename) {
    mRomFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    try {
        mRomFile.open(filename, std::ios::in | std::ios::binary);
        mRomFile.read(reinterpret_cast<char*>(mHeader.data()), mHeader.size());

        if (mHeader[0] != MAGIC0 || mHeader[1] != MAGIC1 ||
            mHeader[2] != MAGIC2 || mHeader[3] != MAGIC3) {
            throw std::invalid_argument("Invalid NES rom file");
        }

        mPrgRom.size = mHeader[4];
        if (!mPrgRom.size) {
            throw std::invalid_argument("No PRG ROM");
        }

        mPrgRom.data.resize(PRG_ROM_SIZE * mPrgRom.size);
        mPrgRom.index = INES_HEADER_SIZE;

        mChrRom.size = mHeader[5];
        mChrRom.data.resize(CHR_ROM_SIZE * mChrRom.size);
        mChrRom.index = INES_HEADER_SIZE + mPrgRom.data.size();

        mRomFile.seekg(mPrgRom.index);
        mRomFile.read(reinterpret_cast<char*>(mPrgRom.data.data()), static_cast<long>(mPrgRom.data.size()));

        mRomFile.seekg(mChrRom.index);
        mRomFile.read(reinterpret_cast<char*>(mChrRom.data.data()), static_cast<long>(mChrRom.data.size()));
    } catch (std::ifstream::failure& e) {
        std::cerr << "Exception opening/reading ROM file: " << e.what() << "\t";
        exit(EXIT_FAILURE);
    }
}

InstructionDecoder::~InstructionDecoder() {
    mRomFile.close();
}

void InstructionDecoder::decode(const Option opt) {
    switch (opt) {
        case Option::HEADER:
            displayHeader();
            break;
        case Option::DISASSEMBLE:
            disassemble();
            break;
        case Option::PRG:
            displayROM(mPrgRom);
            break;
        case Option::CHR:
            displayROM(mChrRom);
            break;
    }
}

void InstructionDecoder::displayHeader() {
    std::cout << std::format("iNES Header:\n"
                             "    Magic Number: \t{:02X} {:02X} {:02X} {:02X}\n"
                             "    Size of PRG ROM: \t{} ({} count of 16 KB units)\n"
                             "    Size of CHR ROM: \t{} ({} count of 8 KB units)\n"
                             "    Flags 6: \t\t{:#02x}\n"
                             "    Flags 7: \t\t{:#02x}\n"
                             "    Flags 8: \t\t{:#02x}\n"
                             "    Flags 9: \t\t{:#02x}\n"
                             "    Flags 10:\t\t{:#02x}\n"
                             "    Unused padding:\t{:#02x}\n",
                             mHeader[0], mHeader[1], mHeader[2], mHeader[3], mPrgRom.data.size(), mHeader[4],
                             mChrRom.data.size(), mHeader[5], mHeader[6], mHeader[7], mHeader[8], mHeader[9],
                             mHeader[10], mHeader[11]);
}

void InstructionDecoder::displayROM(const Rom& rom) {
    displayFormattedData(rom.data, rom.index);
}

void InstructionDecoder::disassemble() {
    for (uint32_t i = 0; i < mPrgRom.data.size(); ++i) {
        const uint8_t* pData = &mPrgRom.data[i];
        uint8_t opcode = *pData;

        const Mnemonic& mnemonic = mOpcodeTable.find(opcode);

        if (mnemonic.mode != AddressingMode::IMP &&
            mnemonic.mode != AddressingMode::ACC &&
            mnemonic.mode != AddressingMode::UNDEF) {
            std::vector<uint8_t> operands;
            std::string mnemOpr, byteOpr;

            for (int j = 1; j <= mnemonic.operandCount; ++j) {
                operands.push_back(*(pData + j));
            }

            i += mnemonic.operandCount;

            for (int j = 0; j < operands.size(); ++j) {
                byteOpr += std::format("{:02X} ", operands[j]);
                mnemOpr += std::format("{:02X}", operands[operands.size() - j - 1]);
            }

            std::cout << std::format("{:06X}:\t{:02X} {}{}{}\n", mPrgRom.index++, opcode, byteOpr,
                                     operands.size() == 2 ? "\t" : "\t\t",
                                     std::vformat(mnemonic.format, std::make_format_args(mnemOpr)));
        } else {
            std::cout << std::format("{:06X}:\t{:02X}\t\t{}\n", mPrgRom.index++, opcode,
                                     mnemonic.mode == AddressingMode::UNDEF ? "UNDEFINED" : mnemonic.format);
        }
    }
}

void InstructionDecoder::displayFormattedData(const std::vector<uint8_t>& data, const uint16_t index) {
    for (int i = 0; i < data.size() / BYTES_PER_ROW; i += BYTES_PER_ROW) {
        int k = 0;
        char ascii[BYTES_PER_ROW];

        for (int j = i; j < BYTES_PER_ROW + i; ++j) {
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
