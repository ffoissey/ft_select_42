#include "ft_select.h"

void	del_element(void *data, size_t content_size)
{
	(void)content_size;
	free(data);
}

void	del_elem(void *data)
{
	del_element(data, 0);
}

void	reorder_element()
{
	t_env		*env;
	t_list		*lst;
	t_element	*elem;
	size_t		id;

	id = 0;
	env = get_env(GET);
	lst = env->head;
	while (lst != NULL)
	{
		elem = lst->content;
		elem->id = id++;
		if (lst->next == NULL)
			env->queue = lst;
		lst = lst->next;
	}
}

void	suppress_element(void)
{
	t_env	*env;

	env = get_env(GET);
	ft_lstdelnode(&env->head, env->target->content, del_elem);
	reorder_element();
	env->nb_elem--;
	if (env->nb_elem == 0)
		exit_routine(OK);
}

int		ft_putc(int c)
{
	return ((int)write(STDERR_FILENO, &c, 1));
}

void	set_focus(t_list *target, const uint8_t flag)
{
	t_element	*elem;

	elem = (t_element *)target->content;
	if (flag == SET)
		elem->state |= ONFOCUS;
	else if (flag == UNSET)
		elem->state &= ~ONFOCUS;
}

void	get_max_size(void)
{
	t_env		*env;
	t_list		*cur;
	t_element	*elem;
	size_t		len;

	env = get_env(GET);
	cur = env->head;
	len = ((t_element *)(cur->content))->len;
	while (cur != NULL)
	{
		elem = (t_element *)(cur->content);
		if (len < elem->len)
			len = elem->len;
		cur = cur->next;
	}
	env->max_len = len;
}

