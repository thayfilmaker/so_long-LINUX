/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasousa <thasousa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 07:51:50 by sousa             #+#    #+#             */
/*   Updated: 2025/09/20 23:20:40 by thasousa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TILE_SIZE 32

/* --- structs principais --- */
typedef struct s_player
{
	size_t			x;
	size_t			y;
}					t_player;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			**map;
	size_t			lines;
	size_t			cols;
	t_player		*player;
	void			*img_wall;
	void			*img_empty;
	void			*img_player;
	void			*img_collectable;
	void			*img_exit;
	int				total_c;
	int				collected_c;
	int				moves;
	void			*img_player_on_exit;
	int				player_on_exit;
	unsigned long	start_time;
}					t_game;

/* --- structs auxiliares --- */
typedef struct s_counts
{
	int				p;
	int				e;
	int				c;
	int				dx;
	int				dy;
	int				nx;
	int				ny;
	int				old_x;
	int				old_y;
	size_t			y;
}					t_counts;

typedef struct s_mapinfo
{
	char			**m;
	size_t			cols;
	size_t			lines;
}					t_mapinfo;

/* --- utils.c --- */
size_t				ft_strlen(const char *s);
void				ft_putstr_fd(char *s, int fd);
void				ft_error(char *msg);
int					exit_game(t_game *game);
char				*ft_strdup(const char *s);

/* --- map.c --- */
int					load_map(const char *filename, t_game *game);
void				free_map(t_game *game);

/* --- validate_map.c --- */
int					validate_map(t_game *game);
int					check_sizemap(t_game *g);

/* --- validate_utils.c --- */
int					check_full_walls(char *line, size_t len);
int					check_side_walls(char *line, size_t len);
int					count_line_chars(char *line, size_t len, t_counts *cnt);
int					check_counts(t_counts cnt);
int					has_collectibles(t_game *g);

/* --- graphics.c --- */
void				draw_tile(t_game *game, size_t x, size_t y, char tile);
void				redraw_map(t_game *game);
void				load_images(t_game *game);

/* --- player.c --- */
void				move_player(t_game *game, char direction);
int					handle_keypress(int keycode, t_game *game);
void				game_loop(t_game *game);

/* --- player_utils.c --- */
void				get_delta(char dir, int *dx, int *dy);
int					is_blocked(t_game *game, int x, int y);
int					handle_tile(t_game *g, int nx, int ny);
void				print_moves(t_game *g);
void				update_player_pos(t_game *g, int old_x, int old_y);

/* --- path.c --- */
int					check_path(t_game *g);

/* --- path_utils.c --- */
void				free_map_copy(char **map, size_t lines);
int					all_collectibles_reached(char **vis, t_game *g);
int					exit_adjacent_reachable(char **vis, t_game *g);
int					loop_handler(t_game *game);
void				close_game(t_game *game);
unsigned long		timestamp_ms(void);

#endif
