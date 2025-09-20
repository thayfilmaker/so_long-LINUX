/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 06:38:30 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 22:09:02 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map_copy(char **map, size_t lines)
{
	size_t	i;

	if (!map)
		return ;
	i = 0;
	while (i < lines)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	all_collectibles_reached(char **vis, t_game *g)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < g->lines)
	{
		x = 0;
		while (x < g->cols)
		{
			if (g->map[y][x] == 'C' && vis[y][x] != 'F')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	is_f(char **vis, size_t x, size_t y, t_game *g)
{
	if (x >= g->cols || y >= g->lines)
		return (0);
	return (vis[y][x] == 'F');
}

int	exit_adjacent_reachable(char **vis, t_game *g)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < g->lines)
	{
		x = 0;
		while (x < g->cols)
		{
			if (g->map[y][x] == 'E')
			{
				if (is_f(vis, x + 1, y, g) || is_f(vis, x - 1, y, g)
					|| is_f(vis, x, y + 1, g) || is_f(vis, x, y - 1, g))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	loop_handler(t_game *game)
{
	if (game->player_on_exit && game->collected_c == game->total_c)
	{
		if (timestamp_ms() - game->start_time >= 125)
		{
			ft_putstr_fd("VICTORY!!\n", 1);
			close_game(game);
		}
	}
	return (0);
}
