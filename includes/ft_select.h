#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <stdbool.h>

# define GET	NULL
# define OK		NULL

# define UNSET	0
# define SET	1

# define RESET_QUEUE	1

# define NONE		0x00
# define SELECTED	0x01
# define ONFOCUS	0x02

# define KEY_UP			4283163
# define KEY_DOWN		4348699
# define KEY_LEFT		4479771
# define KEY_RIGHT		4414235
# define KEY_SPACE		32
# define KEY_ESCAPE		27
# define KEY_BACKSPACE	127
# define KEY_DEL		2117294875
# define KEY_RETURN		10
# define KEY_TAB		0x09

# define NB_KEY			10

typedef void	(*t_key_process)(void);

// UP - DOWN - LEFT - RIGHT - DEL - BACKSPACE - RETURN - ESC - TAB - SPACE


# define ERR_MALLOC		"Malloc failed"
# define ERR_READ		"Read failed"
# define ERR_IOCTL		"Ioctl failed"
# define ERR_NOTATTY	"Not a tty"
# define ERR_TERMCAP	"All termcaps could not be initialized"
# define ERR_NONPRINT	"Arguments should contain only printable char"
# define ERR_MISS_ARG	"./ft_select needs at least one argument"
# define ERR_TERM_UNSET	"TERM must be set"
# define ERR_DB_ACCESS	"Could not access to the termcap database"
# define ERR_TERM_UNDEF	"Undefined type of terminal"

# define SCREEN_ALERT	"Screen too small"

# define ORIGIN		0
# define CURRENT	1

# define NB_TC	8

enum	e_style
{
	CLEAR,
	MOVE_CURSOR,
	INVISIBLE_CURSOR,
	VISIBLE_CURSOR,
	SELECT,
	UNSELECT,
	FOCUS,
	UNFOCUS
};

typedef struct	s_env
{
	t_list			*head;
	t_list			*queue;
	t_list			*target;
	bool			screen_alert;
	size_t			elem_by_row;
	size_t			elem_by_col;
	size_t			col;
	size_t			row;
	size_t			pad;
	size_t			max_len;
	size_t			nb_elem;
	uint64_t		err;
	char			*tc[NB_TC];
	struct termios	*termmode_origin;
	struct termios	*termmode_current;
}				t_env;

typedef struct	s_element
{
	char		*str;
	size_t		len;
	size_t		id;
	uint64_t	state;
}				t_element;

t_env	*get_env(t_env *env);
void	init_list(int ac, char **av);

void	exit_routine(const char *err);

void	apply_termmode(const uint8_t flag);
void	init_termmode(void);
void	create_termmode(void);

void	init_termcaps(void);

void	right_key(void);
void	left_key(void);
void	down_key(void);
void	up_key(void);
void	escape_key(void);
void	return_key(void);
void	space_key(void);
void	del_key(void);
void	backspace_key(void);

void	display(void);

void	get_max_size(void);
void	del_element(void *data, size_t content_size);
void	del_elem(void *data);
void	set_focus(t_list *target, const uint8_t flag);
int		ft_putc(int c);
void	suppress_element(void);

#endif
