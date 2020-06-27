#include "ft_select.h"

void	sigint_handler(int sig)
{
	(void)sig;
	exit_routine(NULL);
}

void	sigwinch_handler(int sig)
{
	(void)sig;
	display();
}

void	sigtstp_handler(int sig)
{
	char	s[2];

	(void)sig;
	tputs(get_env(GET)->tc[CLEAR], STDERR_FILENO, ft_putc);
	tputs(get_env(GET)->tc[VISIBLE_CURSOR], STDERR_FILENO, ft_putc);
	s[0] = get_env(GET)->termmode_current->c_cc[VSUSP];
	s[1] = '\0';
	if (get_env(GET)->termmode_origin != NULL
			&& get_env(GET)->termmode_current != NULL)
	apply_termmode(ORIGIN);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN_FILENO, TIOCSTI, s);
}

void	sigcont_handler(int sig)
{
	(void)sig;
	signal(SIGTSTP, sigtstp_handler);
	tputs(get_env(GET)->tc[INVISIBLE_CURSOR], STDERR_FILENO, ft_putc);
	if (get_env(GET)->termmode_origin != NULL
			&& get_env(GET)->termmode_current != NULL)
		apply_termmode(CURRENT);
	display();
}

void	init_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	signal(SIGTERM, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGCONT, sigcont_handler);
}
