#ifndef ASM_INSTRUCTIONS_INCLUDED
#define ASM_INSTRUCTIONS_INCLUDED (1)

#include "op.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct s_inst t_inst;

#define args_classes_count (3)
struct s_inst {
    const char* name;
    uint8_t     code;
    uint8_t     args_num;
    bool        args_need_code;
    uint8_t     args_classes[args_classes_count];
    uint8_t     t_dir_size;
};

/* 명령어 목록 */
#define inst_count (16)
static const t_inst g_inst[inst_count] = {
    {
        .name           = "live",
        .code           = 0x01,
        .args_num       = 1,
        .args_need_code = false,
        .args_classes   = { T_DIR, 0, 0 },
        .t_dir_size     = 4,
    },
    {
        .name           = "ld",
        .code           = 0x02,
        .args_num       = 2,
        .args_need_code = true,
        .args_classes   = { T_DIR | T_IND, T_REG, 0 },
        .t_dir_size     = 4,
    },
    {
        .name           = "st",
        .code           = 0x03,
        .args_num       = 2,
        .args_need_code = true,
        .args_classes   = { T_REG, T_REG | T_IND, 0 },
        .t_dir_size     = 4,
    },
    {
        .name           = "add",
        .code           = 0x04,
        .args_num       = 3,
        .args_need_code = true,
        .args_classes   = { T_REG, T_REG, T_REG },
        .t_dir_size     = 4,
    },
    {
        .name           = "sub",
        .code           = 0x05,
        .args_num       = 3,
        .args_need_code = true,
        .args_classes   = { T_REG, T_REG, T_REG },
        .t_dir_size     = 4,
    },
    {
        .name           = "and",
        .code           = 0x06,
        .args_num       = 3,
        .args_need_code = true,
        .args_classes   = { T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG },
        .t_dir_size     = 4,
    },
    {
        .name           = "or",
        .code           = 0x07,
        .args_num       = 3,
        .args_need_code = true,
        .args_classes   = { T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG },
        .t_dir_size     = 4,
    },
    {
        .name           = "xor",
        .code           = 0x08,
        .args_num       = 3,
        .args_need_code = true,
        .args_classes   = { T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG },
        .t_dir_size     = 4,
    },
    {
        .name           = "zjmp",
        .code           = 0x09,
        .args_num       = 1,
        .args_need_code = false,
        .args_classes   = { T_DIR, 0, 0 },
        .t_dir_size     = 2,
    },
    {
        .name           = "ldi",
        .code           = 0x0A,
        .args_num       = 3,
        .args_need_code = true,
        .args_classes   = { T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG },
        .t_dir_size     = 2,
    },
    {
        .name           = "sti",
        .code           = 0x0B,
        .args_num       = 3,
        .args_need_code = true,
        .args_classes   = { T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR },
        .t_dir_size     = 2,
    },
    {
        .name           = "fork",
        .code           = 0x0C,
        .args_num       = 1,
        .args_need_code = false,
        .args_classes   = { T_DIR, 0, 0 },
        .t_dir_size     = 2,
    },
    {
        .name           = "lld",
        .code           = 0x0D,
        .args_num       = 2,
        .args_need_code = true,
        .args_classes   = { T_DIR | T_IND, T_REG, 0 },
        .t_dir_size     = 4,
    },
    {
        .name           = "lldi",
        .code           = 0x0E,
        .args_num       = 3,
        .args_need_code = true,
        .args_classes   = { T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG },
        .t_dir_size     = 2,
    },
    {
        .name           = "lfork",
        .code           = 0x0F,
        .args_num       = 1,
        .args_need_code = false,
        .args_classes   = { T_DIR, 0, 0 },
        .t_dir_size     = 2,
    },
    {
        .name           = "aff",
        .code           = 0x10,
        .args_num       = 1,
        .args_need_code = true,
        .args_classes   = { T_REG, 0, 0 },
        .t_dir_size     = 4,
    }
};

#endif
