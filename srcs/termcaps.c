#include "ft_select.h"

static void	init_termcaps_strings(void)
{
	char		**tc;
	size_t		i;

	tc = get_env(GET)->tc;
	tc[CLEAR] = tgetstr("cl", NULL);
	tc[MOVE_CURSOR] = tgetstr("cm", NULL);
	tc[NEXT_LINE] = tgetstr("do", NULL);
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
