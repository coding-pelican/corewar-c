#ifndef TERMINATE_ERRORS_STR_INCLUDED
#define TERMINATE_ERRORS_STR_INCLUDED (1)

#include "str.h"
#include "terminate_errors.h"

static const t_str_const terminate_errors[] = {
    literal_str(MEMORY_ALLOCATION),
    literal_str(FILE_OPENING),
    literal_str(FILE_READING),
    literal_str(FILE_INVALID),
    literal_str(INVALID_MAGIC),
    literal_str(NULL_BYTES),
    literal_str(CODE_SIZE),
    literal_str(CHAMPS_NUM)
};
static const usize terminate_errors_len = sizeof(terminate_errors) / sizeof(t_str_const);

#endif /* TERMINATE_ERRORS_STR_INCLUDED */
