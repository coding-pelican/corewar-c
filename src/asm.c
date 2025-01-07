#include "asm.h"

#include <stdio.h>

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        // Print usage message and exit if incorrect number of arguments
        ignore fprintf(stderr, "Usage: ./asm champ.s\n");
        return 1;
    }

    if (!check_file_extension(argv[1], "s")) {
        // Print error message for invalid file extension
        ignore fprintf(stderr, "ERROR: Invalid file extension\n");
        return 1;
    }

    if (!asm_to_bytecode(argv[1])) {
        // Print error message for processing failure
        ignore fprintf(stderr, "ERROR: Processing failed\n");
        return 1;
    }

    return 0; // Successfully processed the file
}
