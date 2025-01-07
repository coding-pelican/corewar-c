#include "asm.h"
#include "str.h"

// get_entities: 엔티티를 분석하여 처리하는 함수
int get_entities(t_pars* pars, char** row) {
    char current_char = (*row)[pars->col];

    if (current_char == '\n' && (++(pars->col))) {
        add_entity(&(pars->entities), new_entity(pars, ENDLINE));
    } else if (current_char == SEPARATOR_CHAR && (++(pars->col))) {
        add_entity(&(pars->entities), new_entity(pars, SEPARATOR));
    } else if (is_command(pars, *row)) {
        parse_command(pars, *row, new_entity(pars, COMMAND));
    } else if (current_char == DIRECT_CHAR && (++(pars->col))) {
        handle_direct(pars, row);
    } else if (current_char == '"') {
        parse_str(pars, row, pars->col, new_entity(pars, STRING));
    } else if (current_char == LABEL_CHAR) {
        parse_chars(pars, *row, (pars->col)++, new_entity(pars, INDIRECT_LABEL));
    } else {
        parse_int(pars, *row, pars->col, new_entity(pars, INDIRECT));
    }

    return 1;
}

// handle_direct: DIRECT_CHAR와 관련된 처리 함수
void handle_direct(t_pars* pars, char** row) {
    if ((*row)[pars->col] == LABEL_CHAR && (++(pars->col))) {
        parse_chars(pars, *row, pars->col - 2, new_entity(pars, DIRECT_LABEL));
    } else {
        parse_int(pars, *row, pars->col - 1, new_entity(pars, DIRECT));
    }
}

// parse_chars: 라벨 또는 명령어 처리 함수
void parse_chars(t_pars* pars, char* row, int start, t_entity* entity) {
    size_t col = pars->col;

    entity->col = start + 1;
    while (row[pars->col] != '\0' && strchr(LABEL_CHARS, row[pars->col])) {
        ++(pars->col);
    }

    if ((pars->col - col) && row[pars->col] == LABEL_CHAR && (++(pars->col))) {
        entity->content = strndup(row + start, pars->col - start);
        if (!entity->content) {
            terminate(MEMORY_ALLOCATION);
        }
        entity->class = LABEL;
        add_entity(&(pars->entities), entity);
    } else if ((pars->col - col) && is_delimiter(row[pars->col])) {
        entity->content = strndup(row + start, pars->col - start);
        if (!entity->content) {
            terminate(MEMORY_ALLOCATION);
        }
        if (entity->class == INDIRECT) {
            entity->class = class_is_register(entity->content) ? REGISTER : INSTRUCTION;
        }
        add_entity(&(pars->entities), entity);
    } else {
        terminate_lexical(entity->row, entity->col);
    }
}

// parse_int: 정수 값을 처리하는 함수
void parse_int(t_pars* pars, char* row, int start, t_entity* entity) {
    size_t col = pars->col;

    entity->col = start + 1;
    if (row[pars->col] == '-') {
        ++(pars->col); // 음수 처리
    }

    while (isdigit(row[pars->col])) {
        ++(pars->col);
    }

    if ((pars->col - col) && (entity->class == DIRECT || is_delimiter(row[pars->col]))) {
        entity->content = strndup(row + start, pars->col - start);
        if (!entity->content) {
            terminate(MEMORY_ALLOCATION);
        }
        add_entity(&(pars->entities), entity);
    } else if (entity->class != DIRECT) {
        pars->col = start;
        parse_chars(pars, row, start, entity);
    } else {
        terminate_lexical(pars->row, start);
    }
}

// parse_str: 문자열을 처리하는 함수
void parse_str(t_pars* pars, char** row, int start, t_entity* entity) {
    long long size = 1;
    char*     str  = NULL;
    char*     end  = NULL;

    entity->col = start;
    while (!(end = strchr(*row + start + 1, '"')) && (size = read_next_line(pars->fd, &str))) {
        *row = join_str(row, &str);
        if (!(*row)) {
            terminate(MEMORY_ALLOCATION);
        }
    }

    upd_pars_row_and_col(pars, *row);

    if (!size) {
        terminate_lexical(pars->row, pars->col);
    }

    entity->content = strndup(*row + start + 1, end - (*row) - start - 1);
    if (!entity->content) {
        terminate(MEMORY_ALLOCATION);
    }

    if (end - pars->col != *row) {
        upd_row(row, end - pars->col);
    }

    ++(pars->col);
    add_entity(&(pars->entities), entity);
}

// parse_command: 명령어를 처리하는 함수
void parse_command(t_pars* pars, char* row, t_entity* entity) {
    entity->col = pars->col + 1;
    if (strncmp(row + pars->col, NAME_CMD_STRING, strlen(NAME_CMD_STRING)) == 0) {
        entity->class   = COMMAND_NAME;
        entity->content = strndup(row + pars->col, strlen(NAME_CMD_STRING));
        if (!entity->content) {
            terminate(MEMORY_ALLOCATION);
        }
        pars->col += strlen(NAME_CMD_STRING);
    } else {
        entity->class   = COMMAND_COMMENT;
        entity->content = strndup(row + pars->col, strlen(COMMENT_CMD_STRING));
        if (!entity->content) {
            terminate(MEMORY_ALLOCATION);
        }
        pars->col += strlen(COMMENT_CMD_STRING);
    }
    add_entity(&(pars->entities), entity);
}
