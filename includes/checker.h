#ifndef CHECKER_H
#define CHECKER_H

/*struct*/
typedef struct node
{
	struct node	*next;
	struct node	*parent;
	int			x;
	int			y;
}				t_node;

typedef struct s_gdata
{
	char **map;
	int st_pos[2];
	int c[3];
	int f[3];
	char *texures[4];
	int res_x;
	int res_y;
	int map_x;
	int map_y;
}				t_gdata;

typedef struct s_data {
	void	*s;
	void	*win;
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
/*libs headers*/
#include <stdio.h>
#include <mlx.h>
#include "../libft/libft.h"
/*Functions prototype*/
int	find_longest_row(char **map, t_gdata *d);
int read_map(int fd, t_gdata *data);
void draw_map(t_gdata *d, t_data *data);
#endif
