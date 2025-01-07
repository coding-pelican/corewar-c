#include "asm.h"

// get_data: 주어진 타입(NAME 또는 COMMENT)에 따라 데이터를 처리하는 함수
void get_data(t_pars* pars, t_entity** curr, int type) {
    // 이미 데이터가 존재하면 구문 오류 발생
    if ((type == NAME && pars->name != NULL) || (type == COMMENT && pars->comment != NULL)) {
        terminate_syntax(pars, *curr, false);
    }

    *curr = (*curr)->next;

    // 해당 엔티티가 STRING이 아니면 구문 오류 발생
    if ((*curr)->class != STRING) {
        terminate_syntax(pars, *curr, false);
    }

    if (type == NAME) {
        if (strlen((*curr)->content) > PROG_NAME_LENGTH) {
            terminate_big_bio(NAME);
        }
        pars->name = strdup((*curr)->content);
        if (!pars->name) {
            terminate(MEMORY_ALLOCATION);
        }
    } else if (type == COMMENT) {
        if (strlen((*curr)->content) > COMMENT_LENGTH) {
            terminate_big_bio(COMMENT);
        }
        pars->comment = strdup((*curr)->content);
        if (!pars->comment) {
            terminate(MEMORY_ALLOCATION);
        }
    }
    *curr = (*curr)->next;
    if ((*curr)->class != ENDLINE) {
        terminate_syntax(pars, *curr, false);
    }
}

// get_champ_bio: 챔피언의 이름과 코멘트를 처리하는 함수
void get_champ_bio(t_pars* pars, t_entity** curr) {
    while (pars->name == NULL || pars->comment == NULL) {
        if ((*curr)->class == COMMAND_NAME) {
            get_data(pars, curr, NAME);
        } else if ((*curr)->class == COMMAND_COMMENT) {
            get_data(pars, curr, COMMENT);
        } else {
            terminate_syntax(pars, *curr, false);
        }
        *curr = (*curr)->next;
    }
}

// read_and_proc_entities: 엔티티를 읽고 처리하는 함수
void read_and_proc_entities(t_pars* pars, t_entity** curr) {
    bool was_label = false;
    if ((*curr)->class == END) {
        terminate_syntax(pars, *curr, false);
    }

    while ((*curr)->class != END) {
        if (pars->pos >= pars->code_size) {
            upd_buffer(pars);
        }

        pars->op_pos = pars->pos;

        if ((*curr)->class == LABEL) {
            was_label = true;
            proc_label(pars, curr);
        }

        if (was_label && (*curr)->class == END) {
            terminate_syntax(pars, *curr, false);
        }

        if (was_label && (*curr)->class != INSTRUCTION && (*curr)->class != ENDLINE) {
            break;
        }

        if ((*curr)->class == INSTRUCTION) {
            proc_instruction(pars, curr);
        }

        if ((*curr)->class == ENDLINE) {
            *curr = (*curr)->next;
        } else {
            (*curr)->class == END ? terminate_syntax(pars, pars->end, true) : terminate_entity(*curr);
        }
    }

    insert_ints_instead_mentions(pars);
}
