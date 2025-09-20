/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:20:11 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 21:55:22 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	draw_tile(t_game *game, size_t x, size_t y, char tile)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img_empty, x
		* TILE_SIZE, y * TILE_SIZE);
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x
			* TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->img_collectable, x
			* TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->img_exit, x
			* TILE_SIZE, y * TILE_SIZE);
}

void	redraw_map(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->lines)
	{
		x = 0;
		while (x < game->cols)
		{
			draw_tile(game, x, y, game->map[y][x]);
			x++;
		}
		y++;
	}
	if (game->map[game->player->y][game->player->x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->img_player_on_exit,
			game->player->x * TILE_SIZE, game->player->y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->img_player,
			game->player->x * TILE_SIZE, game->player->y * TILE_SIZE);
}

static void	check_images(t_game *game)
{
	if (!game->img_wall || !game->img_empty || !game->img_player
		|| !game->img_collectable || !game->img_exit
		|| !game->img_player_on_exit)
		ft_error("Error loading images");
}

void	load_images(t_game *game)
{
	int	w;
	int	h;

	w = TILE_SIZE;
	h = TILE_SIZE;
	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"images/wall.xpm", &w, &h);
	game->img_empty = mlx_xpm_file_to_image(game->mlx,
			"images/empty.xpm", &w, &h);
	game->img_player = mlx_xpm_file_to_image(game->mlx,
			"images/player.xpm", &w, &h);
	game->img_player_on_exit = mlx_xpm_file_to_image(game->mlx,
			"images/player_on_exit.xpm", &w, &h);
	game->img_collectable = mlx_xpm_file_to_image(game->mlx,
			"images/collectable.xpm", &w, &h);
	game->img_exit = mlx_xpm_file_to_image(game->mlx,
			"images/exit.xpm", &w, &h);
	check_images(game);
}
