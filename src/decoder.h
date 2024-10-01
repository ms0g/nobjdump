#pragma once

#include <fstream>
#include <string>
#include <vector>

enum class Options {
    HEADER,
    DISASSEMBLE,
    PRG,
    CHR,
};

enum class Opcode : uint8_t {
    RTI=0x40,
    RTS=0x60,
    BRK=0x00,
    PHP=0x08,
    PLP=0x28,
    PHA=0x48,
    PLA=0x68,
    DEY=0x88,
    TAY=0xA8,
    INY=0xC8,
    INX=0xE8,
    BCS=0xB0,
    BCC=0x90,
    BEQ=0xF0,
    BNE=0xD0,
    BPL=0x10,
    BMI=0x30,
    BVC=0x50,
    BVS=0x70,
    SEC=0x38,
    SEI=0x78,
    SED=0xF8,
    CLD=0xD8,
    CLV=0xB8,
    CLC=0x18,
    CLI=0x58,
};

class InstructionDecoder {
public:
    explicit InstructionDecoder(const std::string& filename);
    
    ~InstructionDecoder();
    
    void decode(Options opt);

    InstructionDecoder(const InstructionDecoder&) = delete;
    InstructionDecoder& operator=(const InstructionDecoder&) = delete;

private:
    std::ifstream mRomFile;
    std::vector<uint8_t> mHeader;
    std::vector<uint8_t> mPrgData;
    std::vector<uint8_t> mChrData;
    uint8_t mPrgBankSize;
    uint8_t mChrBankSize;
};