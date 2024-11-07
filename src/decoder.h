#pragma once

#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include "opcodeTable.h"

#define ROM(n) struct {         \
    std::vector<uint8_t> data;  \
    uint16_t index;             \
    uint8_t size;               \
    } n                         \

enum class Option {
    HEADER,
    DISASSEMBLE,
    PRG,
    CHR
};


class InstructionDecoder {
public:
    explicit InstructionDecoder(const char* filename);

    ~InstructionDecoder();

    void decode(Option opt);

private:
    void displayHeader();

    void displayPRG();

    void displayCHR();

    void disassemble();

    template<typename T>
    void displayFormattedData(const T& data, uint16_t index);

    std::ifstream mRomFile;
    std::array<uint8_t, 16> mHeader{};
    ROM(mPrgRom);
    ROM(mChrRom);

    OpcodeTable mOpcodeTable;

    static constexpr uint8_t MAGIC0 = 0x4E;
    static constexpr uint8_t MAGIC1 = 0x45;
    static constexpr uint8_t MAGIC2 = 0x53;
    static constexpr uint8_t MAGIC3 = 0x1A;

    static constexpr int PRG_ROM_SIZE = 16384;
    static constexpr int CHR_ROM_SIZE = 8192;
    static constexpr int BYTES_PER_ROW = 16;
    static constexpr int INES_HEADER_SIZE = 16;
};