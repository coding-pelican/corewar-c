#include "asm.h"


// proc_label: 라벨을 처리하는 함수
void proc_label(t_pars *pars, t_entity **curr)
{
    char *name;
    t_label *label;

    // 라벨 이름 추출 (마지막 ':' 문자를 제외한 이름)
    name = strndup((*curr)->content, strlen((*curr)->content) - 1);
    if (!name)
        terminate(MEMORY_ALLOCATION);

    // 라벨이 이미 존재하지 않으면 새로 추가
    label = find_label(pars->labels, name);
    if (!label) {
        add_label(&(pars->labels), new_label(pars->op_pos, name));
    }

    if (label && label->op_pos == -1) {
        label->op_pos = pars->pos;
    }

    free(name);
    *curr = (*curr)->next;
}

// proc_instruction: 명령어를 처리하는 함수
void proc_instruction(t_pars *pars, t_entity **curr)
{
    int8_t code;
    t_inst *inst;

    // 명령어를 가져오기
    inst = get_instruction((*curr)->content);
    if (!inst)
        terminate_instruction(*curr);

    pars->code[pars->pos++] = inst->code;
    *curr = (*curr)->next;

    if (inst->args_need_code) {
        ++(pars->pos);
    }

    // 인자 처리
    code = read_and_code_args(pars, curr, inst);

    // 인자 코드가 필요하면, 해당 위치에 코드 저장
    if (inst->args_need_code) {
        pars->code[pars->op_pos + 1] = code;
    }
}
