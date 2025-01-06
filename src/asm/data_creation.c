#include "asm.h"

// new_entity: 새로운 엔티티를 생성
t_entity *new_entity(t_pars *pars, t_class class)
{
    t_entity *entity = malloc(sizeof(t_entity));
    if (!entity)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    entity->class = class;
    entity->row = pars->row;
    entity->col = pars->col;
    entity->next = NULL;

    if (entity->class == SEPARATOR)
    {
        entity->content = strdup(",");
        if (!entity->content)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }

    return entity;
}

// new_label: 새로운 라벨을 생성
t_label *new_label(int op_pos, char *name)
{
    t_label *label = malloc(sizeof(t_label));
    if (!label)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    label->op_pos = op_pos;
    label->name = strdup(name);
    if (!label->name)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    return label;
}

// new_mention: 새로운 멘션을 생성
t_mention *new_mention(t_pars *pars, t_entity *entity, size_t size)
{
    t_mention *mention = malloc(sizeof(t_mention));
    if (!mention)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    mention->size = size;
    mention->pos = pars->pos;
    mention->op_pos = pars->op_pos;
    mention->row = entity->row;
    mention->col = entity->col;
    mention->next = NULL;

    return mention;
}

// new_pars: 새로운 파서를 생성
t_pars *new_pars(int fd)
{
    t_pars *pars = malloc(sizeof(t_pars));
    if (!pars)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    pars->fd = fd;
    return pars;
}
