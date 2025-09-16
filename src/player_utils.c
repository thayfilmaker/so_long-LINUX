/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 02:57:05 by sousa             #+#    #+#             */
/*   Updated: 2025/09/16 23:45:11 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int is_blocked(t_game *g, int nx, int ny)
{
    if (nx < 0 || ny < 0 || nx >= (int)g->cols || ny >= (int)g->lines)
        return (1);  // fora do mapa bloqueia
    return (g->map[ny][nx] == '1');
}

int handle_tile(t_game *g, int nx, int ny)
{
    if (g->map[ny][nx] == 'C')
    {
        g->map[ny][nx] = '0';  // coleta o item
        g->collected_c++;
        return (1);
    }
    if (g->map[ny][nx] == 'E')
    {
        if (g->collected_c < g->total_c)
        {
            ft_putstr_fd("Ainda restam coletáveis!\n", 1);
            return (1);  // não deixa sair sem coletar tudo
        }
        ft_putstr_fd("Você venceu!\n", 1);
        exit_game(g);
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
	static int	moves = 0;

	(void)g;
	moves++;
	ft_putstr_fd("Movimentos: ", 1);
	print_number(moves);
	ft_putstr_fd("\n", 1);
}
