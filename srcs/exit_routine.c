#include "ft_select.h"

static void	print_onfocus(t_list *lst)
{
	t_element	*element;
	t_vector	*output;

	output = NULL;
	while (lst != NULL)
	{
		element = (t_element *)lst->content;
		if (element != NULL && element->state == ONFOCUS)
		{
			if (output == NULL)
			{
				if ((output = vct_newstr(element->str)) == NULL)
					exit_routine(ERR_MALLOC);
			}
			else
			{
				vct_add(output, ' ');
				vct_addstr(output, element->str);
			}
		}
		lst = lst->next;
	}
	if (output != NULL)
		vct_print(output);
}

void	exit_routine(const char *err)
{
	t_env *env;

	env = get_env(GET);
	if (err != NULL)
		ft_dprintf(STDERR_FILENO, "ERROR: %s\n", err);
	else
	{
		tputs(env->tc[CLEAR], STDERR_FILENO, ft_putc);
		print_onfocus(env->head);
	}
	if (env->termmode_origin != NULL && env->termmode_current != NULL)
		apply_termmode(ORIGIN);
	free(env->termmode_origin);
	free(env->termmode_current);
	ft_lstdel(&env->head, del_element);
	(void)env;
	exit(err == NULL ? EXIT_SUCCESS : EXIT_FAILURE);
}
