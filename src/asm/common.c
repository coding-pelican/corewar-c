# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <ctype.h>
# include <unistd.h>
# include <stdarg.h>

bool check_file_extension(const char *file, const char *ext)
{
    // 파일명에서 마지막 '.' 위치를 찾음
    const char *last_point = strrchr(file, '.');

    // 확장자가 없거나 '.'이 파일명 시작일 경우 false 반환
    if (!last_point || last_point == file)
        return false;

    // 확장자 비교 (대소문자 구분)
    return strcmp(last_point + 1, ext) == 0;
}

void terminate(const char *message)
{
    // 에러 메시지 출력
    fprintf(stderr, "ERROR: %s\n", message);

    if (system("leaks -q asm") != 0) {
        fprintf(stderr, "Warning: 'leaks' command failed or is not available.\n");
    }

    // 프로그램 종료
    exit(EXIT_FAILURE);
}
