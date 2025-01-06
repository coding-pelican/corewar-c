#include "asm.h"

// read_and_code_args: 인자들을 읽고 코드로 변환하는 함수
int8_t read_and_code_args(t_pars *pars, t_entity **curr, t_inst *inst)
{
    int8_t code = 0;
    int8_t arg_class;
    int arg_num = 0;

    while (arg_num < inst->args_num)
    {
        // 현재 엔티티가 유효한 인자 타입인지 확인
        if ((*curr)->class == REGISTER || (*curr)->class == DIRECT
            || (*curr)->class == DIRECT_LABEL || (*curr)->class == INDIRECT
            || (*curr)->class == INDIRECT_LABEL)
        {
            arg_class = get_one_arg(pars, curr, inst, arg_num);
            
            // 코드에 해당 인자 타입을 반영
            code |= get_type_code(arg_class) << (2 * (3 - arg_num));

            *curr = (*curr)->next;
        }
        else
        {
            terminate_syntax(pars, *curr, false);
        }

        // 인자가 끝난 후 구분자를 확인하고 처리
        if (arg_num++ < inst->args_num - 1)
        {
            if ((*curr)->class == SEPARATOR)
                *curr = (*curr)->next;
            else
                terminate_invalid_parameter_count(inst);
        }
    }
    return code;
}

// get_one_arg: 하나의 인자를 처리하는 함수
int8_t get_one_arg(t_pars *pars, t_entity **curr, t_inst *inst, int arg_num)
{
    int8_t arg_class;

    arg_class = get_arg_type((*curr)->class);

    // 유효한 인자 타입인지 확인
    if ((inst->args_classes[arg_num] & arg_class) == 0)
        terminate_invalid_argument(inst, arg_num, *curr);

    // 각 타입에 맞게 처리
    if (arg_class == T_REG)
        proc_reg(pars, (*curr)->content + 1);  // 레지스터 처리
    if ((*curr)->class == DIRECT_LABEL || (*curr)->class == INDIRECT_LABEL)
        proc_mention(pars, *curr, inst);  // 라벨 처리
    if ((*curr)->class == DIRECT || (*curr)->class == INDIRECT)
        proc_int(pars, *curr, inst);  // 숫자 처리

    return arg_class;
}

// proc_reg: 레지스터를 처리하는 함수
void proc_reg(t_pars *pars, char *reg_number)
{
    // 레지스터 번호를 바이트코드에 기록
    write_to_bytecode(pars->code, pars->pos, atoi(reg_number), 1);
    pars->pos++;
}

// proc_mention: 라벨을 처리하는 함수
void proc_mention(t_pars *pars, t_entity *curr, t_inst *inst)
{
    t_label *label;
    char *name;
    int start;
    size_t size;

    // 라벨 이름 처리 시작 위치 결정
    start = (curr->class == INDIRECT_LABEL) ? 1 : 2;
    size = (curr->class == INDIRECT_LABEL) ? IND_SIZE : inst->t_dir_size;

    // 라벨 이름 추출
    name = strndup(curr->content + start, strlen(curr->content) - start);
    if (!name)
        terminate(MEMORY_ALLOCATION);

    // 라벨을 찾고 없으면 새로 생성
    if (!(label = find_label(pars->labels, name)))
    {
        label = new_label(-1, name);
        add_label(&(pars->labels), label);
    }

    add_mention(&(label->mentions), new_mention(pars, curr, size));

    pars->pos += size;
    free(name);
}

// proc_int: 숫자를 처리하는 함수
void proc_int(t_pars *pars, t_entity *curr, t_inst *inst)
{
    int start;
    size_t size;

    // 숫자 시작 위치와 크기 결정
    start = (curr->class == INDIRECT) ? 0 : 1;
    size = (curr->class == INDIRECT) ? IND_SIZE : inst->t_dir_size;

    // 숫자 값을 바이트코드에 기록
    write_to_bytecode(pars->code, pars->pos, atoi32(&(curr->content[start])), size);
    pars->pos += size;
}

// atoi32: 문자열을 32비트 정수로 변환
int32_t atoi32(const char *str)
{
    int32_t result = 0;
    int sign = 1;

    while (isspace(*str)) str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-') sign = -1;
        str++;
    }
    while (isdigit(*str))
    {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}

