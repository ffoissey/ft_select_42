#include "ft_select.h"

void		create_termmode(void)
{
	struct termios	term;
	t_env			*env;

	env = get_env(GET);
	env->termmode_origin = (struct termios *)malloc(sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, &term) == SUCCESS)
	{
		ft_memcpy(env->termmode_origin, &term, sizeof(struct termios));
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		term.c_lflag |= ISIG;
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		env->termmode_current = (struct termios *)malloc(sizeof(struct termios));
		if (env->termmode_current != NULL)
			ft_memcpy(env->termmode_current, &term, sizeof(struct termios));
	}
	if (env->termmode_current == NULL || env->termmode_origin == NULL)
		exit_routine("Failed to set termmode");
}

void		apply_termmode(const uint8_t flag)
{
	t_env	*env;

	env = get_env(GET);
	if (env->termmode_origin != NULL && env->termmode_current != NULL)
	{
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, (flag & CURRENT) ?
				env->termmode_current : env->termmode_origin) == FAILURE)
			exit_routine("Failed to apply termmode");
	}
	else
		exit_routine("termmode: unexpected error");
}

void	init_termmode(void)
{
	create_termmode();
	apply_termmode(CURRENT);
}
