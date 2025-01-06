#include "asm.h"

// is_delimiter: 주어진 문자가 구분자(delimiter)인지 확인
bool is_delimiter(char c)
{
    return (isspace(c) || c == '"' || c == '\0' || 
            c == DIRECT_CHAR || c == SEPARATOR_CHAR || 
            c == COMMENT_CHAR || c == ANOTHER_COMMENT_CHAR);
}

// divide_str: 문자열을 줄 단위로 나누기
int divide_str(char **str, char **row)
{
    char *div = strchr(*str, '\n'); // '\n' 위치를 찾음
    char *new;

    if (!div)
        return (0); // '\n'이 없으면 0 반환

    div++; // '\n' 다음 위치로 이동
    if (!(*row = strndup(*str, div - *str)))
        terminate(MEMORY_ALLOCATION);

    if (!strlen(div)) // '\n' 이후 문자열이 없으면 메모리 해제
    {
        free(*str);
        *str = NULL;
    }
    else
    {
        if (!(new = strdup(div)))
            terminate(MEMORY_ALLOCATION);
        free(*str);
        *str = new;
    }

    return 1;
}

// read_next_line: 파일에서 한 줄을 읽어오는 함수
int read_next_line(int fd, char **row)
{
    static char *str = NULL; // static 변수로 상태 유지
    char buff[BUFF_SIZE + 1];
    char *tmp;
    int size;

    // 파일 읽기가 가능한지 확인
    if (read(fd, buff, 0) < 0)
        return -1;

    // str 초기화 및 줄 끝 '\n' 확인
    while (str == NULL || !strchr(str, '\n'))
    {
        size = read(fd, buff, BUFF_SIZE);
        if (size == 0) // EOF에 도달했을 때 처리
        {
            if (str == NULL || !*str) // 더 이상 읽을 데이터가 없으면 종료
            {
                *row = NULL;
                return 0;
            }
            *row = str; // 마지막 줄 반환
            str = NULL;
            return 1;
        }

        buff[size] = '\0'; // 버퍼 끝에 null 문자 추가
        tmp = str; // 기존 문자열 저장
        if (!(str = tmp ? malloc(strlen(tmp) + strlen(buff) + 1) : strdup(buff)))
            terminate(MEMORY_ALLOCATION);
        if (tmp)
        {
            strcpy(str, tmp); // 기존 문자열 복사
            strcat(str, buff); // 새로 읽은 내용 추가
            free(tmp); // 이전 메모리 해제
        }
    }

    return divide_str(&str, row); // 줄을 분리하여 반환
}

// join_str: 두 문자열을 결합하는 함수
char *join_str(char **s1, char **s2)
{
    char *res = malloc(strlen(*s1) + strlen(*s2) + 1);
    if (!res)
        terminate(MEMORY_ALLOCATION);
    strcpy(res, *s1);
    strcat(res, *s2);
    free(*s1); // 첫 번째 문자열 메모리 해제
    *s1 = NULL; // 포인터 초기화
    free(*s2); // 두 번째 문자열 메모리 해제
    *s2 = NULL; // 포인터 초기화
    return res;
}

// class_is_register: 주어진 문자열이 레지스터인지 확인
bool class_is_register(char *str)
{
    int len = strlen(str);

    if ((len == 2 || len == 3) && str[0] == 'r') // 'r'로 시작하고 길이가 2 또는 3인지 확인
    {
        int i = 1;
        while (str[i] && isdigit(str[i])) // 숫자인지 확인
            i++;
        return (str[i] == '\0' && atoi(&str[1]) > 0); // 끝까지 숫자이고 값이 양수인지 확인
    }
    return false;
}

// upd_row: row를 ptr로 업데이트
void upd_row(char **row, char *ptr)
{
    char *new;

    new = strdup(ptr);
    if (!new)
        terminate(MEMORY_ALLOCATION);
    free(*row);
    *row = new;
}

// upd_pars_row_and_col: pars의 행(row)과 열(col)을 업데이트
void upd_pars_row_and_col(t_pars *pars, const char *row)
{
    size_t i;

    i = pars->col;
    while (row[++i] != '\0' && row[i] != '"')
    {
        if (row[i] == '\n')
        {
            pars->row++;
            pars->col = 0;
        }
        else
        {
            pars->col++;
        }
    }
}

// skip_whitespaces: 공백을 건너뛰고 열 위치를 업데이트
int skip_whitespaces(int *col, char *row)
{
    while (isspace(row[*col]) && row[*col] != '\n')
        (*col)++;
    return 1;
}

// skip_comment: 주석을 건너뛰고 열 위치를 업데이트
int skip_comment(int *col, const char *row)
{
    if (row[*col] == COMMENT_CHAR || row[*col] == ANOTHER_COMMENT_CHAR)
    {
        while (row[*col] != '\0' && row[*col] != '\n')
            (*col)++;
    }
    return 1;
}

// is_command: 주어진 row가 NAME_CMD_STRING 또는 COMMENT_CMD_STRING인지 확인
bool is_command(t_pars *pars, char *row)
{
    return ((!strncmp(row + pars->col, NAME_CMD_STRING, strlen(NAME_CMD_STRING)) && 
            is_delimiter(row[pars->col + strlen(NAME_CMD_STRING)])) ||
            (!strncmp(row + pars->col, COMMENT_CMD_STRING, strlen(COMMENT_CMD_STRING)) && 
            is_delimiter(row[pars->col + strlen(COMMENT_CMD_STRING)])));
}

// upd_buffer: pars의 code를 새로운 크기로 재할당하여 업데이트
int upd_buffer(t_pars *pars)
{
    pars->code_size += CHAMP_MAX_SIZE;
    pars->code = realloc(pars->code, pars->code_size);
    if (!pars->code)
        terminate(MEMORY_ALLOCATION);
    return 1;
}

// find_label: 주어진 name을 가진 label을 labels에서 찾아 반환
t_label *find_label(t_label *labels, char *name)
{
    while (labels)
    {
        if (strcmp(labels->name, name) == 0)
            return labels;
        labels = labels->next;
    }
    return NULL;
}

// get_instruction: 주어진 name에 해당하는 instruction을 찾아 반환
t_inst *get_instruction(char *name)
{
    for (int i = 0; i < 16; ++i)
    {
        if (strcmp(g_inst[i].name, name) == 0)
            return &(g_inst[i]);
    }
    return NULL;
}

// get_type_code: 주어진 type에 대응하는 type code를 반환
int8_t get_type_code(int8_t type)
{
    if (type == T_REG)
        return REG_CODE;
    if (type == T_DIR)
        return DIR_CODE;
    return IND_CODE;
}

// get_arg_type: class에 맞는 argument type을 반환
int get_arg_type(t_class class)
{
    if (class == REGISTER)
        return T_REG;
    if (class == DIRECT_LABEL || class == DIRECT)
        return T_DIR;
    return T_IND;
}
