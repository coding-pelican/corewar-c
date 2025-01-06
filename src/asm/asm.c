#include "common.h"
#include "asm.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        // Print usage message and exit if incorrect number of arguments
        fprintf(stderr, "Usage: ./asm champ.s\n");
        return 1;
    }

    // Validate file extension and process if valid
    if (check_file_extension(argv[1], "s") && asm_to_bytecode(argv[1]))
    {
        return 0; // Successfully processed the file
    }

    // Print error for invalid filename or processing failure
    fprintf(stderr, "ERROR: Invalid filename or processing failed\n");
    return 1;
}
