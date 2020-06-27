#include "ft_select.h"

void	right_key(void)
{
	t_env	*env;

	env = get_env(GET);
	if (env->nb_elem < 2)
		env->target = env->head;
	else
	{
		if (env->target == NULL || env->target->next == NULL)
			env->target = env->head;
		else
			env->target = env->target->next;
	}
}

void	left_key(void)
{
	t_env	*env;
	t_list	*run;

	env = get_env(GET);
	if (env->nb_elem < 2)
		env->target = env->head;
	else
	{
		run = env->head;
		if (run == env->target)
			env->target = env->queue;
		else
		{
			while (run->next != env->target && run->next != NULL)
				run = run->next;
			env->target = run;
		}
	}
}

void	up_key(void)
{
	t_env	*env;
	int		target_id;
	int		cur_id;

	env = get_env(GET);
	if (env->nb_elem < 2 || env->elem_by_col < 2)
		env->target = env->head;
	else
	{
		cur_id = ((t_element *)(((t_list *)(env->target))->content))->id;
		target_id = (int)cur_id - (int)env->elem_by_row;
		if (target_id < 0)
			target_id = (env->nb_elem - 1)
				- ((env->nb_elem - 1) % env->elem_by_row) + cur_id;
		if (target_id >= (int)env->nb_elem)
			target_id -= env->elem_by_row;
		while (target_id != cur_id)
		{
			left_key();
			cur_id = ((t_element *)(((t_list *)(env->target))->content))->id;
			if (cur_id % env->nb_elem == target_id % env->nb_elem)
				break ;
		}
	}
}

void	down_key(void)
{
	t_env	*env;
	size_t	target_id;
	size_t	cur_id;

	env = get_env(GET);
	if (env->nb_elem < 2 || env->elem_by_col < 2)
		env->target = env->head;
	else
	{
		cur_id = ((t_element *)(((t_list *)(env->target))->content))->id;
		target_id = cur_id + env->elem_by_row;
		if (target_id >= env->nb_elem )
			target_id = cur_id % env->elem_by_row; 
		while (target_id != cur_id)
		{
			right_key();
			cur_id = ((t_element *)(((t_list *)(env->target))->content))->id;
			if (cur_id % env->nb_elem == target_id % env->nb_elem)
				break ;
		}
	}
}
