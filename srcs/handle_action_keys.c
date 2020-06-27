#include "ft_select.h"

void	backspace_key(void)
{
	t_env		*env;
	t_list		*next_target;

	env = get_env(GET);
	next_target = env->target->next;
	suppress_element();
	if (next_target == env->head)
		env->target = env->head;
	else
	{
		env->target = next_target;
		left_key();
	}
}

void	del_key(void)
{
	t_env		*env;
	t_list		*next_target;

	env = get_env(GET);
	next_target = env->target->next;
	suppress_element();
	if (next_target == NULL)
		env->target = env->queue;
	else
		right_key();
}

void	space_key(void)
{
	t_list		*node;
	t_element	*target;

	node = (t_list *)(get_env(GET)->target);
	if (node != NULL && node->content != NULL)
	{
		target = (t_element *)node->content;
		if (target->state & SELECTED)
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
	tputs(env->tc[CLEAR], STDERR_FILENO, ft_putc);
	exit_routine(OK);
}

void	return_key(void)
{
	get_env(GET)->print = true;
	exit_routine(OK);
}
