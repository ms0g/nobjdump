#include <iostream>
#include <cstring>
#include "decoder.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 1
#define VERSION_PATCH 1

#define STRINGIFY0(s) # s
#define STRINGIFY(s) STRINGIFY0(s)
#define VERSION STRINGIFY(VERSION_MAJOR) "." STRINGIFY(VERSION_MINOR) "." STRINGIFY(VERSION_PATCH)

int main(int argc, char** argv) {
    static const char* usage = "OVERVIEW: NES ROM image dumper\n\n"
                               "USAGE: nobjdump [options] <input rom image>\n\n"
                               "OPTIONS:\n"
                               "  --header              Display iNES header\n"
                               "  -d, --disassemble     Display the assembler mnemonics for the machine instructions\n"
                               "  -c, --chr             Display CHR ROM data\n"
                               "  -p, --prg             Display PRG ROM data\n"
                               "  -h, --help            Display available options\n"
                               "  -v, --version         Display the version of this program\n";
    if (argc < 3) {
        if (argc == 2 && (!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help"))) {
            std::cout << usage << std::endl;
        } else if (argc == 2 && (!std::strcmp(argv[1], "-v") || !std::strcmp(argv[1], "--version"))) {
            std::cout << "nobjdump version " << VERSION << std::endl;
        } else {
            std::cerr << usage << std::endl;
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    Option opt;

    if (!std::strcmp(argv[1], "--header")) {
        opt = Option::HEADER;
    } else if (!std::strcmp(argv[1], "-d") || !std::strcmp(argv[1], "--disassemble")) {
        opt = Option::DISASSEMBLE;
    } else if (!std::strcmp(argv[1], "-c") || !std::strcmp(argv[1], "--chr")) {
        opt = Option::CHR;
    } else if (!std::strcmp(argv[1], "-p") || !std::strcmp(argv[1], "--prg")) {
        opt = Option::PRG;
    } else {
        std::cerr << usage << std::endl;
        return EXIT_FAILURE;
    }

    InstructionDecoder decoder{argv[2]};
    decoder.decode(opt);

    return EXIT_SUCCESS;
}
