/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 06:38:01 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 19:07:05 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	flood(t_mapinfo *info, size_t x, size_t y)
{
	if (x >= info->cols || y >= info->lines)
		return ;
	if (info->m[y][x] == '1' || info->m[y][x] == 'F')
		return ;
	if (info->m[y][x] == 'E')
		return ;
	info->m[y][x] = 'F';
	flood(info, x + 1, y);
	flood(info, x - 1, y);
	flood(info, x, y + 1);
	flood(info, x, y - 1);
}

static int	find_p(t_mapinfo *info, size_t *px, size_t *py)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < info->lines)
	{
		x = 0;
		while (x < info->cols)
		{
			if (info->m[y][x] == 'P')
			{
				*px = x;
				*py = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static char	**copy_map(t_game *g)
{
	char	**cpy;
	size_t	i;

	cpy = malloc(sizeof(char *) * (g->lines + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < g->lines)
	{
		cpy[i] = ft_strdup(g->map[i]);
		if (!cpy[i])
		{
			free_map_copy(cpy, i);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

int	check_path(t_game *g)
{
	t_mapinfo	info;
	size_t		px;
	size_t		py;

	info.m = copy_map(g);
	if (!info.m)
		return (0);
	info.lines = g->lines;
	info.cols = g->cols;
	if (!find_p(&info, &px, &py))
		return (free_map_copy(info.m, g->lines), 0);
	flood(&info, px, py);
	if (!all_collectibles_reached(info.m, g))
		return (free_map_copy(info.m, g->lines), 0);
	if (!exit_adjacent_reachable(info.m, g))
		return (free_map_copy(info.m, g->lines), 0);
	free_map_copy(info.m, g->lines);
	return (1);
}
