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
           "    Size of PRG ROM: \t%d (%d count of 16 KB units)\n"
           "    Size of CHR ROM: \t%d (%d count of 8 KB units)\n"
           "    Flags 6: \t\t0x%02x\n"
           "    Flags 7: \t\t0x%02x\n"
           "    Flags 8: \t\t0x%02x\n"
           "    Flags 9: \t\t0x%02x\n"
           "    Flags 10:\t\t0x%02x\n"
           "    Unused padding:\t0x%02x\n",
           header[0], header[1], header[2], header[3], prgRom.size, header[4],
           chrRom.size, header[5], header[6], header[7], header[8], header[9],
           header[10], header[11]);
}

static void displayROM(const Rom* rom) {
    displayFormattedData(rom->data, rom->size, rom->address);
}

static void displayFormattedData(const uint8_t* data, const size_t len, const uint16_t index) {
    for (int i = 0; i < len / BYTES_PER_ROW; i += BYTES_PER_ROW) {
        int k = 0;
        char ascii[BYTES_PER_ROW];

        for (int j = i; j < BYTES_PER_ROW + i; ++j) {
            ascii[k++] = isprint(data[j]) ? data[j] : '.';
        }

        printf("%06X:\t%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X"
               "  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", index + i,
               data[i], data[i + 1], data[i + 2], data[i + 3], data[i + 4], data[i + 5], data[i + 6],
               data[i + 7], data[i + 8], data[i + 9], data[i + 10], data[i + 11], data[i + 12],
               data[i + 13], data[i + 14], data[i + 15], ascii[0], ascii[1], ascii[2], ascii[3],
               ascii[4], ascii[5], ascii[6], ascii[7], ascii[8], ascii[9], ascii[10], ascii[11],
               ascii[12], ascii[13], ascii[14], ascii[15]);
    }
}

static void disassemble() {
    for (uint32_t i = 0; i < prgRom.size; ++i) {
        const uint8_t* pData = &prgRom.data[i];
        const uint8_t opcode = *pData;

        const Mnemonic* mnemonic = opFindMnemonic(opcode);

        if (mnemonic->aMode != IMP && mnemonic->aMode != ACC && mnemonic->aMode != UNDEF) {
            i += mnemonic->operandCount;

            uint8_t* operands = malloc(mnemonic->operandCount * sizeof(int8_t));

            for (int j = 1; j <= mnemonic->operandCount; ++j) {
                operands[j - 1] = *(pData + j);
            }

            char byteOpr[BUFFER_SIZE] = "";
            char mnemOpr[BUFFER_SIZE] = "";
            char temp[BUFFER_SIZE] = "";
            for (int j = 0; j < mnemonic->operandCount; ++j) {
                snprintf(temp, sizeof(temp), "%02X ", operands[j]);
                strncat(byteOpr, temp, sizeof(byteOpr) - strlen(byteOpr) - 1);

                const uint8_t operand = operands[mnemonic->operandCount - j - 1];
                if (mnemonic->aMode == REL) {
                    snprintf(temp, sizeof(temp), "%02X", prgRom.address + (int8_t)operand + 2);
                } else {
                    snprintf(temp, sizeof(temp), "%02X", operand);
                }

                strncat(mnemOpr, temp, sizeof(mnemOpr) - strlen(mnemOpr) - 1);
            }

            free(operands);

            char out[BUFFER_SIZE] = "";
            snprintf(out, sizeof(out), mnemonic->format, mnemOpr);
            printf("%06X:\t%02X %s%s%s\n", prgRom.address, opcode, byteOpr,
                   mnemonic->operandCount == 2 ? "\t" : "\t\t", out);
        } else {
            printf("%06X:\t%02X\t\t%s\n", prgRom.address, opcode,
                   mnemonic->aMode == UNDEF ? "UNDEFINED" : mnemonic->format);
        }
        prgRom.address += mnemonic->operandCount + 1;
    }
}
