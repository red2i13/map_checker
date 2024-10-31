#include "../includes/checker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	enqueue(t_node **queue, int x, int y)
{
	t_node	*new_t_node;

	new_t_node = malloc(sizeof(t_node));
	if (!new_t_node)
		return (1);
	new_t_node->x = x;
	new_t_node->y = y;
	if ((*queue) == NULL)
	{
		(*queue) = new_t_node;
		(*queue)->parent = 0;
		(*queue)->next = 0;
	}
	else
	{
		new_t_node->next = (*queue)->next;
		new_t_node->parent = (*queue);
		(*queue)->next = new_t_node;
	}
	return (EXIT_SUCCESS);
}

void	dequeue(t_node **list, t_node *current)
{
	t_node	*tmp;
	t_node	*previous;

	if (!list || !*list || !current)
		return ;
	if (*list == current)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		return ;
	}
	else
	{
		previous = *list;
		while (previous->next != current && previous->next != NULL)
			previous = previous->next;
		if (previous->next == current)
			previous->next = current->next;
		else
			return ;
	}
	free(current);
	return ;
}

int	neighbors(t_node **queue, t_node *cur, t_gdata *d, int **vis)
{
	int	x;
	int	y;

	x = cur->x;
	y = cur->y;
	if (x + 1 < d->map_y - 1 && (d->map[x + 1][y] != '1' && d->map[x
			+ 1][y] != ' ') && vis[x + 1][y] == 0)
	{
		enqueue(queue, x + 1, y);
		d->map[x + 1][y] = '5';
	}
	if (x - 1 > 0 && (d->map[x - 1][y] != '1' && d->map[x - 1][y] != ' ')
		&& vis[x - 1][y] == 0)
	{
		enqueue(queue, x - 1, y);
		d->map[x - 1][y] = '5';
	}
	if (y + 1 < d->map_x - 1 && (d->map[x][y + 1] != '1' && d->map[x][y
		+ 1] != ' ') && vis[x][y + 1] == 0)
	{
		enqueue(queue, x, y + 1);
		d->map[x][y + 1] = '5';
	}
	if (y - 1 > 0 && (d->map[x][y - 1] != '1' && d->map[x][y - 1] != ' ')
		&& vis[x][y - 1] == 0)
	{
		enqueue(queue, x, y - 1);
		d->map[x][y - 1] = '5';
	}
	return (EXIT_SUCCESS);
}

int	init_row(int **arr, int i, char **map, int len_r)
{
	int	j;

	j = 0;
	(void)map;
	arr[i] = (int *)malloc(sizeof(int) * len_r);
	if (!arr[i])
	{
		//free_arr(d, (void **)arr, i, 0);
		return (1);
	}
	while (j < len_r)
	{
		arr[i][j] = 0;
		j++;
	}
	return (EXIT_SUCCESS);
}
int	find_longest_row(char **map, t_gdata *d)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		if(ft_strchr(map[i], 'P'))
		{
			d->st_pos[0] = i;
			d->st_pos[1] = ft_strchr(map[i], 'P') - map[i];
		}
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	bfs(int st_x, int st_y, t_gdata *d, t_data *data)
{
	t_node	*queue;
	int		**arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(int *) * d->map_y);
	if (!arr)
		return (1);
	while (i < d->map_y)
	{
		if (init_row(arr, i, d->map, d->map_x))
			return (1);
		i++;
	}
	queue = NULL;
	enqueue(&queue, st_x, st_y);
	while (queue)
	{
		arr[queue->x][queue->y] = 6;
		d->map[queue->x][queue->y] = '6';
		neighbors(&queue, queue, d, arr);
		dequeue(&queue, queue);
		draw_map(d, data);
		usleep(80000);
	}
	//d->bmap = arr;
	return (EXIT_SUCCESS);
}
// for making a tester

int	cross_win(t_data *d)
{
	mlx_destroy_window(d->s, d->win);
	mlx_destroy_display(d->s);
	free(d->s);
	exit(0);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void color_square(int x, int y, int color, t_data *d)
{
	for(int i = 0; i < 32; i++)
	{
		for(int j = 0; j < 32; j++)
		{
			if(i == 0 || j == 0 || i == 32 -1 || j == 32 -1)
				my_mlx_pixel_put(d, x * 32 + i, y * 32 + j, 0x000000);
			else
				my_mlx_pixel_put(d, x * 32 + i, y * 32 + j, color);
		}
	}
}
int     close_win(int key_press, t_data *d)
{
        if (key_press == 65307)
        {
                cross_win(d);
        }
        return (EXIT_SUCCESS);
}
void draw_map(t_gdata *d, t_data *data)
{
	for(int i = 0; d->map[i]; i++)
	{
		for(int j = 0; d->map[i][j]; j++)
		{
			if(d->map[i][j] == '1')
				color_square(j, i, 0x00FF0000, data);
			else if(d->map[i][j] == '0')
				color_square(j, i, 0x00FFFFFF, data);
			else if(d->map[i][j] == '6')
				color_square(j, i, 0x0000FF00, data);
			else if(d->map[i][j] == '5')
				color_square(j, i, 0x000000FF, data);
			else if(d->map[i][j] == 'P')
				color_square(j, i, 0x00FF00FF, data);
		}
	}
	mlx_put_image_to_window(data->s, data->win, data->img, 0, 0);

}
int main(int ac, char **av)
{
	t_data d;
	t_gdata st;

	if(ac < 2)
	{
		printf("Please provide the map to the program\n");
		return(1);
	}
	read_map(open(av[1], 0644), &st);
	d.s = mlx_init();
	//printf("x : %i y : %i", st.map_x, st.map_y);
	d.win = mlx_new_window(d.s,  st.map_x * 32, st.map_y * 32, "Hello World!");
	d.img = mlx_new_image(d.s, st.map_x * 32, st.map_y * 32);
	d.addr = mlx_get_data_addr(d.img, &d.bits_per_pixel, &d.line_length, &d.endian);
	draw_map(&st, &d);
	bfs(st.st_pos[0], st.st_pos[1], &st, &d);
	mlx_hook(d.win, 17, 1L << 0, cross_win, &d);
	mlx_hook(d.win, 3, 1L << 1, close_win, &d);
	mlx_loop(d.s);
	// mlx_destroy_window(ptr, win);
	return(0);
}
