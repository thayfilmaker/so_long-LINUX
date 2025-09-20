/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 02:57:05 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 21:54:26 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	is_blocked(t_game *g, int nx, int ny)
{
	if (nx < 0 || ny < 0 || nx >= (int)g->cols || ny >= (int)g->lines)
		return (1);
	return (g->map[ny][nx] == '1');
}

int	handle_tile(t_game *g, int nx, int ny)
{
	if (g->map[ny][nx] == 'C')
	{
		g->map[ny][nx] = '0';
		g->collected_c++;
		return (1);
	}
	if (g->map[ny][nx] == 'E')
	{
		if (g->collected_c < g->total_c)
		{
			ft_putstr_fd("Collectibles remain!\n", 1);
			return (1);
		}
		g->start_time = timestamp_ms();
		g->moves++;
		print_moves(g);
		loop_handler(g);
	}
	return (1);
}

int	has_collectibles(t_game *g)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < g->lines)
	{
		x = 0;
		while (x < g->cols)
		{
			if (g->map[y][x] == 'C')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static void	print_number(int n)
{
	char	c;

	if (n >= 10)
		print_number(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

void	print_moves(t_game *g)
{
	ft_putstr_fd("Moviments: ", 1);
	print_number(g->moves);
	ft_putstr_fd("\n", 1);
}
