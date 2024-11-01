#include "../includes/checker.h"

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
		usleep(60000);
	}
	free_arr((void **)arr, d->map_y - 1);
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
void free_arr(void **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}
// for making a tester



