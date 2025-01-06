#include "asm.h"

// add_entity: 주어진 엔티티를 리스트에 추가
void add_entity(t_entity **lst, t_entity *new)
{
	t_entity *tmp = *lst;

	if (tmp)
	{
		// ENDLINE이 아닌 경우만 새 엔티티를 추가
		while (tmp->next)
			tmp = tmp->next;
		if (!(new->class == ENDLINE && tmp->class == ENDLINE))
			tmp->next = new;
		else
			free(new);
	}
	else if (new->class != ENDLINE)
	{
		*lst = new;
	}
	else
	{
		free(new);
	}
}

// add_label: 주어진 라벨을 라벨 리스트에 추가
void add_label(t_label **labels, t_label *new)
{
	t_label *tmp = *labels;

	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	// 리스트가 비어 있다면 새 라벨을 첫 번째 항목으로 추가
	else
	{
		*labels = new;
	}
}

// add_mention: 주어진 멘션을 멘션 리스트에 추가
void add_mention(t_mention **mentions, t_mention *new)
{
	t_mention *tmp = *mentions;

	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	// 리스트가 비어 있다면 새 멘션을 첫 번째 항목으로 추가
	else
	{
		*mentions = new;
	}
}
