#include "ft_select.h"

void	del_key(void)
{
	t_env	*env;
	t_list	*run;
	bool	reorder;

	env = get_env(GET);
	if (env->target == env->queue)
	{
		reorder = false;
		run = env->head;
		while (run != NULL)
		{
			if (run->next == env->target)
			{
				reorder = true;
				if (run->next == NULL)
					env->queue = run;
				run = run->next;
				continue ;
			}
			if (reorder == true)
				((t_element *)(run->content))->id--;
			run = run->next;
		}
	}
	ft_lstdelnode(&env->head, env->target->content, del_elem);
	env->nb_elem--;
	if (env->nb_elem == 0)
		exit_routine(OK);
	left_key();
}

void	space_key(void)
{
	t_element	*target;

	target = (t_element *)(get_env(GET)->target);
	if (target != NULL)
	{
		if (target->state & ONFOCUS)
			target->state &= ~SELECTED;
		else
			target->state |= SELECTED;
		right_key();
	}
}

void	escape_key(void)
{
	t_env	*env;

	env = get_env(GET);
	ft_lstdel(&env->head, del_element);
	exit_routine(OK);
}

void	return_key(void)
{
	exit_routine(OK);
}
