#include "asm.h"

#include <stdlib.h>

// free_pars: 파서 객체와 그 내부의 모든 자원을 해제
void free_pars(t_pars** pars) {
    t_entity* entity_next = NULL;
    t_label*  label_next  = NULL;

    free((*pars)->name);
    free((*pars)->comment);
    free((*pars)->code);

    while ((*pars)->entities) {
        entity_next = (*pars)->entities->next;
        free_entity(&((*pars)->entities));
        (*pars)->entities = entity_next;
    }

    while ((*pars)->labels) {
        label_next = (*pars)->labels->next;
        free_label(&((*pars)->labels));
        (*pars)->labels = label_next;
    }

    free(*pars);
}

// free_label: 라벨 객체와 그 관련된 모든 자원을 해제
void free_label(t_label** label) {
    t_mention* mention_next = NULL;

    while ((*label)->mentions) {
        mention_next = (*label)->mentions->next;
        free((*label)->mentions);
        (*label)->mentions = mention_next;
    }

    free((*label)->name);
    free(*label);
}

// free_entity: 엔티티 객체와 그 관련된 자원을 해제
void free_entity(t_entity** entity) {
    free((*entity)->content);
    free(*entity);
}
