#include "asm.h"

// 에러 메시지를 출력하는 함수
static void print_error(const char *message, int row, int col, const char *content, const char *class_name)
{
    printf(message, row, col, class_name, content);
}

// 종료 처리 함수
static void exit_with_error()
{
    exit(1);
}

void terminate_lexical(int row, int col)
{
    print_error("Lexical error at [%d:%d]\n", row, col, "", "");
    exit_with_error();
}

void terminate_entity(t_entity *entity)
{
    print_error("Unexpected token \"%s\" %s at [%d:%d]\n", entity->row, entity->col, entity->content, g_class[entity->class]);
    exit_with_error();
}

void terminate_syntax(t_pars *pars, t_entity *entity, bool suggestion)
{
    if (suggestion)
    {
        printf("Syntax error - unexpected end of input "
               "(Perhaps you forgot to end with a newline ?)\n");
    }
    else
    {
        pars->end->col = pars->col + 1;
        pars->end->row = pars->row + (pars->row == 0);
        print_error("Syntax error at token [TOKEN][%03d:%03d] %s \"%s\"\n", 
                     entity->row, entity->col, g_class[entity->class], entity->content);
    }
    exit_with_error();
}

void terminate_big_bio(int type)
{
    const char *type_name = (type == NAME) ? "name" : "comment";
    printf("Champion %s too long (Max length %d)\n", type_name, 
           (type == NAME) ? PROG_NAME_LENGTH : COMMENT_LENGTH);
    exit_with_error();
}

void terminate_instruction(t_entity *entity)
{
    print_error("Invalid instruction at token [TOKEN][%03d:%03d] "
                "INSTRUCTION \"%s\"\n", entity->row, entity->col, entity->content, "INSTRUCTION");
    exit_with_error();
}

static void print_error_and_exit(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    exit(1);
}

void terminate_invalid_argument(t_inst *inst, int arg_num, t_entity *entity)
{
    char *str = malloc(strlen(g_class[entity->class]) + 1);
    if (str == NULL) {
        print_error_and_exit("Memory allocation failed\n");
    }

    // 소문자 변환
    for (size_t i = 0; g_class[entity->class][i] != '\0'; ++i) {
        str[i] = (char)tolower((unsigned char)g_class[entity->class][i]);
    }
    str[strlen(g_class[entity->class])] = '\0';

    print_error_and_exit("Invalid parameter %d type %s for instruction \"%s\"\n", 
                          arg_num, str, inst->name);
    free(str);  // 메모리 해제
}

void terminate_label(t_label *label)
{
    print_error_and_exit("No such label %s while attempting to dereference token "
                          "[TOKEN][%03d:%03d] DIRECT_LABEL \"%s:%s\"\n", 
                          label->name, label->mentions->row, label->mentions->col, label->name);
}

void terminate_invalid_parameter_count(t_inst *inst)
{
    print_error_and_exit("Invalid parameter count for instruction %s\n", inst->name);
}
