#ifndef DECODER_H
#define DECODER_H

typedef enum {
    HEADER,
    DISASSEMBLE,
    PRG,
    CHR
} Option;

void initDecoder(const char* filename);

void exitDecoder();

void decode(Option opt);

#endif

