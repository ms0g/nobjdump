#ifndef DECODER_H
#define DECODER_H

typedef enum {
    HEADER,
    DISASSEMBLE,
    PRG,
    CHR
} Option;

void decInit(const char* filename);

void decExit();

void decode(Option opt);

#endif

