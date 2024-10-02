#include <iostream>
#include "decoder.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_PATCH 0

#define STRINGIFY0(s) # s
#define STRINGIFY(s) STRINGIFY0(s)
#define VERSION STRINGIFY(VERSION_MAJOR) "." STRINGIFY(VERSION_MINOR) "." STRINGIFY(VERSION_PATCH)

int main(int argc, char** argv) {
    static const char* usage = "OVERVIEW: NES ROM image dumper\n\n"
                               "USAGE: nobjdump [options] <input rom image>\n\n"
                               "OPTIONS:\n"
                               "  --header              Display ines header\n"
                               "  -d, --disassemble     Display the assembler mnemonics for "
                               "the machine instructions from the rom file\n"
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
            std::cout << usage << std::endl;
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    Option opt;

    if (!std::strcmp(argv[1], "--header")) {
        opt = Option::HEADER;
    } else if (!std::strcmp(argv[1], "--d") || !std::strcmp(argv[1], "--disassemble")) {
        opt = Option::DISASSEMBLE;
    } else if (!std::strcmp(argv[1], "-c") || !std::strcmp(argv[1], "--chr")) {
        opt = Option::CHR;
    } else if (!std::strcmp(argv[1], "-p") || !std::strcmp(argv[1], "--prg")) {
        opt = Option::PRG;
    }

    std::string romfn;
    romfn = argv[2];

    InstructionDecoder decoder{romfn};
    decoder.decode(opt);

    return EXIT_SUCCESS;
}
