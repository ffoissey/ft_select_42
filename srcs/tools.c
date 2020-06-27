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

