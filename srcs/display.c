#include "ft_select.h"

static void	get_screen_info()
{
	t_env			*env;
	struct winsize	win;

	env = get_env(GET);
	env->screen_alert = false;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win) == FAILURE
			|| win.ws_col == 0 || win.ws_row == 0)
		exit_routine(ERR_IOCTL);
	env = get_env(GET);
	env->col = win.ws_col;
	env->row = win.ws_row;
	env->elem_by_row = (env->max_len == 0) ? 0 : env->col / env->max_len;
	if (env->col < env->max_len || env->elem_by_row == 0)
		env->screen_alert = true;
	else
		env->elem_by_col = env->elem_by_row / env->elem_by_row;
	if (env->elem_by_col > env->row)
		env->screen_alert = true;
	if (env->screen_alert == false)
		env->pad = env->max_len;
	
}

void	print_element(t_element *elem)
{
	t_env	*env;

	env = get_env(GET);
	if (elem->state & ONFOCUS)
		tputs(env->tc[FOCUS], STDERR_FILENO, ft_putc);
	if (elem->state & SELECTED)
		tputs(env->tc[SELECT], STDERR_FILENO, ft_putc);
	ft_putstr_fd(elem->str, STDERR_FILENO);
	if (elem->state & SELECTED)
		tputs(env->tc[UNSELECT], STDERR_FILENO, ft_putc);
	if (elem->state & ONFOCUS)
		tputs(env->tc[UNFOCUS], STDERR_FILENO, ft_putc);
}

void	display(void)
{
	t_env	*env;
	t_list	*cur;
	size_t	col;
	size_t	row;

	env = get_env(GET);
	tputs(env->tc[CLEAR], STDERR_FILENO, ft_putc);
	get_screen_info();
	if (env->screen_alert == true)
	{
		ft_dprintf(STDERR_FILENO, SCREEN_ALERT);
		return ;
	}
	cur = env->head;
	col = 0;
	row = 0;
	while (cur != NULL)
	{
		print_element(cur->content);
		row += env->pad;
		if (row >= env->row)
		{
			row = 0;
			col++;
		}
		tputs(tgoto(env->tc[MOVE_CURSOR], row, col), STDERR_FILENO, ft_putc);
		cur = cur->next;
	}
}
