#include "asm.h"

#include <stdlib.h>

void write_to_bytecode(char* code, int pos, int32_t data, size_t size) {
    int8_t i = 0;

    while (size) {
        code[pos + (size - 1)] = (char)((data >> i) & 0xFF);
        --size;
        i += 8;
    }
}

void write_code_to_bytecode(t_pars* pars, int fd) {
    char* bcode = NULL;
    int   len   = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 + pars->pos;

    bcode = (char*)malloc(len + 1);
    if (bcode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    write_to_bytecode(bcode, 0, COREWAR_EXEC_MAGIC, 4);

    memcpy(bcode + 4, pars->name, strlen(pars->name));

    write_to_bytecode(bcode, 4 + PROG_NAME_LENGTH + 4, pars->pos, 4);

    memcpy(bcode + 4 + PROG_NAME_LENGTH + 4 + 4, pars->comment, strlen(pars->comment));

    memcpy(bcode + 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4, pars->code, pars->pos);

    if (write(fd, bcode, len) < 0) {
        perror("Write to file failed");
        free(bcode);
        exit(EXIT_FAILURE);
    }

    free(bcode);
}
