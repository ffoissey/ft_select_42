#include "ft_select.h"

static void	init_termcaps_strings(void)
{
	char		**tc;
	size_t		i;

	tc = get_env(GET)->tc;
	tc[CLEAR] = tgetstr("cl", NULL);
	tc[MOVE_CURSOR] = tgetstr("cm", NULL);
	tc[INVISIBLE_CURSOR] = tgetstr("vi", NULL);
	tc[VISIBLE_CURSOR] = tgetstr("ve", NULL);
	tc[SELECT] = tgetstr("so", NULL);
	tc[UNSELECT] = tgetstr("se", NULL);
	tc[UNFOCUS] = tgetstr("ue", NULL);
	tc[FOCUS] = tgetstr("us", NULL);
	i = 0;
	while (i < NB_TC)
	{
		if (tc[i++] == NULL)
			exit_routine(ERR_TERMCAP);
	}
}

void	init_termcaps(void)
{
	int		ret;
	char	*term;

	term = getenv("TERM");
	if (term == NULL)
		exit_routine(ERR_TERM_UNSET);
	ret = tgetent(NULL, term);
	if (ret == FAILURE)
		exit_routine(ERR_DB_ACCESS);
	else if (ret == 0)
		exit_routine(ERR_TERM_UNDEF);
	init_termcaps_strings();
}
