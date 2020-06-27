#include "ft_select.h"

static void	apply_key(unsigned int mask)
{
	static t_key_process		key_process[NB_KEY] = {up_key, down_key, left_key,
									right_key, space_key, escape_key, del_key,
									del_key, return_key, left_key};
	static const unsigned int	key_code[NB_KEY] = {KEY_UP, KEY_DOWN, KEY_LEFT,
									KEY_RIGHT, KEY_SPACE, KEY_ESCAPE,
									KEY_BACKSPACE, KEY_DEL,	KEY_RETURN,
									KEY_TAB};
	size_t					i;
	t_env					*env;

	i = 0;
	while (i < NB_KEY)
	{
		if (mask == key_code[i])
		{
			env = get_env(GET);
			set_focus(env->target, SET);
			key_process[i]();
			set_focus(env->target, UNSET);
			display();
			break ;
		}
		i++;
	}
}

static void	read_loop(void)
{
	char	buf[4];
	ssize_t	ret;

	ft_bzero(&buf, 4);
	display();
	while ((ret = read(STDIN_FILENO, buf, 4)) > 0)
	{
		apply_key(*((unsigned int *)buf));
		ft_bzero(&buf, 4);
	}
	if (ret == FAILURE)
		exit_routine(ERR_READ);
}

int		main(int ac, char **av)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	get_env(&env);
	init_list(ac, av);
	init_termcaps();
	init_termmode();
	read_loop();	
	exit_routine(OK);
	return (EXIT_SUCCESS);
}
