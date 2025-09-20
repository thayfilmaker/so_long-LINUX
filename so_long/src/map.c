/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 07:53:02 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 22:02:17 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

#define BUFFER_SIZE 1024

static char	*copy_buffer(char *buffer, size_t len)
{
	size_t	i;
	char	*line;

	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	size_t	i;
	int		ret;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		ret = read(fd, &buffer[i], 1);
		if (ret <= 0 || buffer[i] == '\n')
			break ;
		i++;
	}
	if (i == 0 && ret <= 0)
		return (NULL);
	buffer[i] = '\0';
	return (copy_buffer(buffer, i));
}

char	**extend_map(char **map, char *line, size_t lines)
{
	size_t	i;
	char	**new_map;

	new_map = malloc(sizeof(char *) * (lines + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}

char	**read_map_lines(int fd, size_t *lines)
{
	char	*line;
	char	**map;

	map = NULL;
	*lines = 0;
	while (1)
	{
		line = read_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
		{
			free(line);
			free_map_copy(map, *lines);
			return (NULL);
		}
		map = extend_map(map, line, *lines);
		if (!map)
		{
			free(line);
			return (NULL);
		}
		(*lines)++;
	}
	return (map);
}

int	load_map(const char *filename, t_game *game)
{
	int		fd;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error\n", 7);
		perror("open");
		exit(EXIT_FAILURE);
	}
	map = read_map_lines(fd, &game->lines);
	close(fd);
	if (!map)
		return (0);
	game->map = map;
	game->cols = ft_strlen(map[0]);
	return (1);
}
