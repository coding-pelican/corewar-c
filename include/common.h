#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED (1)

#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

#include "def.h"
#include "terminate_errors.h"

#define BUFF_SIZE 1

extern bool check_file_extension(const char* file, const char* ext);
extern void terminate(const char* message);

#endif /* COMMON_INCLUDED */
