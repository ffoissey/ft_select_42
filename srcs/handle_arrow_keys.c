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
		while (run->next != env->target && run->next != NULL)
			run = run->next;
		env->target = (run == env->head) ? env->queue : run;
	}
}

void	up_key(void)
{
	t_env	*env;
	t_list	*run;
	size_t	target_id;

	env = get_env(GET);
	if (env->nb_elem < 2)
		env->target = env->head;
	else
	{
		target_id = (((t_element *)(((t_list *)(env->target))->content))->id
					+ env->elem_by_row) % env->nb_elem;
		run = env->head;
		while (((t_element *)(run->content))->id != target_id)
			run = run->next;
		env->target = run;
	}
}

void	down_key(void)
{
	t_env	*env;
	t_list	*run;
	size_t	target_id;

	env = get_env(GET);
	if (env->nb_elem < 2)
		env->target = env->head;
	else
	{
		target_id = (((t_element *)(((t_list *)(env->target))->content))->id
					+ env->elem_by_row);
		if (target_id < 0)
			target_id = env->nb_elem + target_id;
		run = env->head;
		while (((t_element *)(run->content))->id != target_id)
			run = run->next;
		env->target = run;
	}
}
