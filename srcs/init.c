#include "ft_select.h"

t_env	*get_env(t_env *env)
{
	static t_env *keeper_env = NULL;

	if (env != NULL)
		keeper_env = env;
	return (keeper_env);
}


static t_element	create_new_element(char *str)
{
	t_element		elem;
	static size_t	id = 0;

	if (ft_strcheck(str, ft_isprint) == false)
		exit_routine(ERR_NONPRINT);
	elem.str = str;
	elem.id = id++;
	elem.state = NONE;
	elem.len = ft_strlen(str) + 1;
	return (elem);
}

void	init_list(int ac, char **av)
{
	t_env		*env;
	t_list		*node;
	t_element	elem;
	int			i;

	env = get_env(GET);
	if (ac == 1)
		exit_routine(ERR_MISS_ARG);
	if (isatty(STDIN_FILENO) == false)
		exit_routine(ERR_NOTATTY);
	i = 1;
	while (i < ac)
	{
		elem = create_new_element(av[i]);
		node = ft_lstnew(&elem, sizeof(t_element));
		if (node == NULL)
			exit_routine(ERR_MALLOC);
		env->queue = node;
		ft_lstadd_back(&env->head, node);
		env->nb_elem++;
		i++;
	}
	get_max_size();
	env->target = env->head;
	set_focus(env->target, SET);
}
