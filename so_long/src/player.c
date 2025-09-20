/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:19:41 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 21:58:49 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_player(t_game *g, char dir)
{
	t_counts	dt;

	get_delta(dir, &dt.dx, &dt.dy);
	dt.nx = g->player->x + dt.dx;
	dt.ny = g->player->y + dt.dy;
	if (is_blocked(g, dt.nx, dt.ny) || !handle_tile(g, dt.nx, dt.ny))
		return ;
	dt.old_x = g->player->x;
	dt.old_y = g->player->y;
	g->player->x = dt.nx;
	g->player->y = dt.ny;
	if (g->map[dt.ny][dt.nx] == 'E')
	{
		g->player_on_exit = 1;
	}
	else
		g->player_on_exit = 0;
	g->moves++;
	print_moves(g);
	update_player_pos(g, dt.old_x, dt.old_y);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 119)
		move_player(game, 'W');
	else if (keycode == 115)
		move_player(game, 'S');
	else if (keycode == 97)
		move_player(game, 'A');
	else if (keycode == 100)
		move_player(game, 'D');
	else if (keycode == 65307)
		exit_game(game);
	return (0);
}

void	game_loop(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Failed to start mlx");
	game->win = mlx_new_window(game->mlx,
			TILE_SIZE * game->cols, TILE_SIZE * game->lines,
			"So Long");
	if (!game->win)
		ft_error("Failed to create window");
	mlx_hook(game->win, 17, 0, exit_game, game);
	load_images(game);
	redraw_map(game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_loop_hook(game->mlx, loop_handler, game);
	mlx_loop(game->mlx);
}

void	update_player_pos(t_game *g, int old_x, int old_y)
{
	draw_tile(g, old_x, old_y, g->map[old_y][old_x]);
	if (g->map[g->player->y][g->player->x] == 'E')
		mlx_put_image_to_window(g->mlx, g->win, g->img_player_on_exit,
			g->player->x * TILE_SIZE, g->player->y * TILE_SIZE);
	else
		mlx_put_image_to_window(g->mlx, g->win, g->img_player, g->player->x
			* TILE_SIZE, g->player->y * TILE_SIZE);
}

void	get_delta(char dir, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (dir == 'W')
		*dy = -1;
	else if (dir == 'S')
		*dy = 1;
	else if (dir == 'A')
		*dx = -1;
	else if (dir == 'D')
		*dx = 1;
}
