/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoissey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 22:57:37 by ffoissey          #+#    #+#             */
/*   Updated: 2020/06/27 22:57:49 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	del_element(void *data, size_t content_size)
{
	(void)content_size;
	free(data);
}

void	del_elem(void *data)
{
	del_element(data, 0);
}

void	suppress_element(void)
{
	t_env	*env;

	env = get_env(GET);
	ft_lstdelnode(&env->head, env->target->content, del_elem);
	reorder_element();
	env->nb_elem--;
	if (env->nb_elem == 0)
	{
		tputs(env->tc[CLEAR], STDERR_FILENO, ft_putc);
		exit_routine(OK);
	}
}
