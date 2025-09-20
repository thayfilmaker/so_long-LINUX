/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:01:44 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 23:26:10 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	reset_counts(t_counts *cnt)
{
	cnt->p = 0;
	cnt->e = 0;
	cnt->c = 0;
}

static int	check_line(t_game *g, size_t y, t_counts *cnt)
{
	if (ft_strlen(g->map[y]) != g->cols)
		return (0);
	if (y == 0 || y == g->lines - 1)
	{
		if (!check_full_walls(g->map[y], g->cols))
			return (0);
	}
	else if (!check_side_walls(g->map[y], g->cols))
		return (0);
	if (!count_line_chars(g->map[y], g->cols, cnt))
		return (0);
	return (1);
}

int	validate_map(t_game *g)
{
	t_counts	cnt;

	if (!g->map || g->lines == 0)
		return (0);
	if (!check_sizemap(g))
	{
		free_map(g);
		ft_error("Invalid size map");
	}
	reset_counts(&cnt);
	cnt.y = 0;
	while (cnt.y < g->lines)
	{
		if (!check_line(g, cnt.y, &cnt))
			return (0);
		cnt.y++;
	}
	g->total_c = cnt.c;
	g->collected_c = 0;
	g->moves = 0;
	if (!check_counts(cnt))
		return (0);
	if (!check_path(g))
		return (0);
	return (1);
}

void	free_map(t_game *g)
{
	size_t	i;

	if (!g->map)
		return ;
	i = 0;
	while (i < g->lines)
	{
		free(g->map[i]);
		i++;
	}
	free(g->map);
	g->map = NULL;
	g->lines = 0;
}
