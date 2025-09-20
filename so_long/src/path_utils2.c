/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:04:19 by thasousa          #+#    #+#             */
/*   Updated: 2025/09/20 23:16:26 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	close_game(t_game *game)
{
	exit_game(game);
}

unsigned long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000UL + tv.tv_usec / 1000UL);
}

int	check_sizemap(t_game *g)
{
	int	l;
	int	c;

	c = 0;
	while (g->map[c])
	{
		l = 0;
		while (g->map[c][l])
		{
			if (l > 61)
				return (0);
			l++;
		}
		if (c > 33)
			return (0);
		c++;
	}
	return (1);
}
