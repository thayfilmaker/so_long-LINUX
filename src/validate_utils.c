/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 02:57:48 by sousa             #+#    #+#             */
/*   Updated: 2025/09/16 19:14:28 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	count_line_chars(char *line, size_t cols, t_counts *cnt)
{
	size_t	x;
	char	c;

	x = 0;
	while (x < cols)
	{
		c = line[x];
		if (c == 'P')
			cnt->p++;
		else if (c == 'E')
			cnt->e++;
		else if (c == 'C')
			cnt->c++;
		else if (c != '0' && c != '1')
			return (0);
		x++;
	}
	return (1);
}

int	check_counts(t_counts cnt)
{
	if (cnt.p != 1)
		return (0);
	if (cnt.e != 1)
		return (0);
	if (cnt.c < 1)
		return (0);
	return (1);
}

int	check_full_walls(char *line, size_t cols)
{
	size_t	x;

	x = 0;
	while (x < cols)
	{
		if (line[x] != '1')
			return (0);
		x++;
	}
	return (1);
}

int	check_side_walls(char *line, size_t cols)
{
	if (cols < 2)
		return (0);
	if (line[0] != '1' || line[cols - 1] != '1')
		return (0);
	return (1);
}
