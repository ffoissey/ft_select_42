/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 22:52:50 by ffoissey          #+#    #+#             */
/*   Updated: 2020/06/27 23:11:38 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	apply_key(unsigned int mask)
{
	static t_key_process		key_process[NB_KEY] = {up_key, down_key,
									left_key, right_key, space_key, escape_key,
									backspace_key, del_key, return_key,
									right_key};
	static const unsigned int	key_code[NB_KEY] = {KEY_UP, KEY_DOWN, KEY_LEFT,
									KEY_RIGHT, KEY_SPACE, KEY_ESCAPE,
									KEY_BACKSPACE, KEY_DEL, KEY_RETURN,
									KEY_TAB};
	size_t						i;
	t_env						*env;

	i = 0;
	while (i < NB_KEY)
	{
		if (mask == key_code[i])
		{
			env = get_env(GET);
			set_focus(env->target, UNSET);
			key_process[i]();
			set_focus(env->target, SET);
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
	tputs(get_env(GET)->tc[INVISIBLE_CURSOR], STDERR_FILENO, ft_putc);
	display();
	while ((ret = read(STDIN_FILENO, buf, 4)) > 0)
	{
		apply_key(*((unsigned int *)buf));
		ft_bzero(&buf, 4);
	}
	if (ret == FAILURE)
		exit_routine(ERR_READ);
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	get_env(&env);
	if (isatty(STDIN_FILENO) == false || isatty(STDERR_FILENO) == false)
		exit_routine(ERR_NOTATTY);
	init_list(ac, av);
	init_termcaps();
	init_termmode();
	init_signal();
	read_loop();
	exit_routine(OK);
	return (EXIT_SUCCESS);
}
