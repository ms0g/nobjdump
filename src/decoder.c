#include "decoder.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "opcode.h"

#define MAGIC0 0x4E
#define MAGIC1 0x45
#define MAGIC2 0x53
#define MAGIC3 0x1A

#define PRG_ROM_SIZE 16384
#define PRG_ROM_ADDRESS 0x8000
#define CHR_ROM_SIZE 8192
#define BYTES_PER_ROW 16
#define INES_HEADER_SIZE 16
#define BUFFER_SIZE 32

#define error(msg) do { fprintf(stderr, "%s", msg); fclose(romFile); exit(EXIT_FAILURE); } while (0)

typedef struct {
    uint16_t address;
    uint32_t size;
    uint8_t* data;
} Rom;

static Rom prgRom;
static Rom chrRom;
static uint8_t header[16];

static void displayHeader();

static void displayROM(const Rom* rom);

static void displayFormattedData(const uint8_t* data, size_t len, uint16_t index);

static void disassemble();

void decInit(const char* filename) {
    FILE* romFile = fopen(filename, "rb");

    fread(header, sizeof(uint8_t), 16, romFile);

    if (header[0] != MAGIC0 || header[1] != MAGIC1 ||
        header[2] != MAGIC2 || header[3] != MAGIC3) {
        error("Invalid NES rom file\n");
    }

    prgRom.size = PRG_ROM_SIZE * header[4];
    if (!prgRom.size) {
        error("No PRG ROM\n");
    }

    prgRom.data = malloc(prgRom.size);
    prgRom.address = PRG_ROM_ADDRESS;

    chrRom.size = CHR_ROM_SIZE * header[5];
    chrRom.data = malloc(chrRom.size);
    chrRom.address = 0;

    fseek(romFile, INES_HEADER_SIZE, SEEK_SET);
    fread(prgRom.data, sizeof(uint8_t), prgRom.size, romFile);

    fseek(romFile, INES_HEADER_SIZE + prgRom.size, SEEK_SET);
    fread(chrRom.data, sizeof(uint8_t), chrRom.size, romFile);

    fclose(romFile);
}

void decExit() {
    free(prgRom.data);
    free(chrRom.data);
}

void decode(const Option opt) {
    switch (opt) {
        case HEADER:
            displayHeader();
            break;
        case DISASSEMBLE:
            disassemble();
            break;
        case PRG:
            displayROM(&prgRom);
            break;
        case CHR:
            displayROM(&chrRom);
            break;
    }
}

static void displayHeader() {
    printf("iNES Header:\n"
           "    Magic Number: \t%02X %02X %02X %02X\n"
           "    Size of PRG ROM: \t%d KB (%d count of 16 KB units)\n"
           "    Size of CHR ROM: \t%d KB (%d count of 8 KB units)\n"
           "    Flags 6: \t\t0x%02x\n"
           "    Flags 7: \t\t0x%02x\n"
           "    Flags 8: \t\t0x%02x\n"
           "    Flags 9: \t\t0x%02x\n"
           "    Flags 10:\t\t0x%02x\n"
           "    Unused padding:\t0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
           header[0], header[1], header[2], header[3], prgRom.size / 1024, header[4],
           chrRom.size / 1024, header[5], header[6], header[7], header[8], header[9],
           header[10], header[11], header[12], header[13], header[14], header[15]);
}

static void displayROM(const Rom* rom) {
    displayFormattedData(rom->data, rom->size, rom->address);
}

static void displayFormattedData(const uint8_t* data, const size_t len, const uint16_t index) {
    for (size_t i = 0; i < len; i += BYTES_PER_ROW) {
        char ascii[BYTES_PER_ROW + 1] = {0};

        printf("%06X:\t", index + (uint16_t)i);

        for (size_t j = 0; j < BYTES_PER_ROW; ++j) {
            const uint8_t byte = data[i + j];
            printf("%02X ", byte);
            ascii[j] = isprint(byte) ? byte : '.';
        }

        ascii[BYTES_PER_ROW] = '\0';
        printf(" %s\n", ascii);
    }
}

static void disassemble() {
    for (uint32_t i = 0; i < prgRom.size; ++i) {
        const uint8_t* pData = &prgRom.data[i];
        uint32_t currentAddr = prgRom.address;
        const uint8_t opcode = *pData;
        const Mnemonic* mnemonic = opFindMnemonic(opcode);

        if (mnemonic->aMode != IMP && mnemonic->aMode != ACC && mnemonic->aMode != UNDEF) {
            i += mnemonic->operandCount;
            uint8_t operands[2] = {0};

            for (int j = 1; j <= mnemonic->operandCount; ++j) {
                operands[j - 1] = *(pData + j);
            }

            char byteOpr[BUFFER_SIZE] = "";
            char mnemOpr[BUFFER_SIZE] = "";
            char temp[BUFFER_SIZE] = "";
            for (int j = 0; j < mnemonic->operandCount; ++j) {
                snprintf(temp, sizeof(temp), "%02X ", operands[j]);
                strncat(byteOpr, temp, sizeof(byteOpr) - strlen(byteOpr) - 1);
            }

            if (mnemonic->aMode == REL) {
                const int8_t relOffset = (int8_t) operands[0];
                const uint16_t relAddr = currentAddr + mnemonic->operandCount + 1 + relOffset;
                snprintf(mnemOpr, sizeof(mnemOpr), "%04X", relAddr);
            } else if (mnemonic->operandCount == 2) {
                snprintf(mnemOpr, sizeof(mnemOpr), "%02X%02X", operands[1], operands[0]); // little-endian
            } else if (mnemonic->operandCount == 1) {
                snprintf(mnemOpr, sizeof(mnemOpr), "%02X", operands[0]);
            }

            char out[BUFFER_SIZE] = "";
            snprintf(out, sizeof(out), mnemonic->format, mnemOpr);
            printf("%06X:\t%02X %s%s%s\n", prgRom.address, opcode, byteOpr,
                   mnemonic->operandCount == 2 ? "\t" : "\t\t", out);
        } else {
            printf("%06X:\t%02X\t\t%s\n", prgRom.address, opcode, mnemonic->format);
        }
        prgRom.address += mnemonic->operandCount + 1;
    }
}
