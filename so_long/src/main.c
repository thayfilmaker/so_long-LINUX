/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 07:54:48 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 23:15:03 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	find_player_start(t_game *g)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < g->lines)
	{
		x = 0;
		while (x < g->cols)
		{
			if (g->map[y][x] == 'P')
			{
				g->player->x = x;
				g->player->y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_error("Uso: ./so_long <mapa.ber>");
	game.map = NULL;
	load_map(argv[1], &game);
	if (!validate_map(&game))
	{
		free_map(&game);
		ft_error("Invalid map");
	}
	game.player = malloc(sizeof(t_player));
	if (!game.player)
		return (0);
	find_player_start(&game);
	game.player_on_exit = 0;
	game.start_time = 0;
	game_loop(&game);
	return (0);
}
