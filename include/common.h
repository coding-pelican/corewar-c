#ifndef COMMON_H
# define COMMON_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <ctype.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

# include "terminate_errors.h"

# define BUFF_SIZE 1

bool	check_file_extension(char *file, char *ext);
void	terminate(char *message);

#endif
