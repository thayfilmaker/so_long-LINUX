/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 07:52:42 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 21:44:33 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_error(char *msg)
{
	write(1, "Error\n", 7);
	ft_putstr_fd(msg, 2);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

int	exit_game(t_game *game)
{
	mlx_loop_end(game->mlx);
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_empty)
		mlx_destroy_image(game->mlx, game->img_empty);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_collectable)
		mlx_destroy_image(game->mlx, game->img_collectable);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_player_on_exit)
		mlx_destroy_image(game->mlx, game->img_player_on_exit);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->player)
		free(game->player);
	free_map(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
