/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:27:37 by hhattaki          #+#    #+#             */
/*   Updated: 2022/12/31 23:02:28 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long_bonus.h"

int	get_x(char	*file)
{
	int		x;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	x = ft_strlen(line) - 1;
	free(line);
	close(fd);
	return (x);
}

int	get_y(char	*file)
{
	char	*line;
	int		fd;
	int		j;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	j = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		j++;
	}
	close (fd);
	return (j);
}

char	**get_map(int fd, int y, int x)
{
	char	**map;
	int		j;
	char	*line;
	int		len;

	map = ft_calloc(y, sizeof(char *));
	j = 0;
	line = get_next_line(fd);
	while (line && j < y)
	{
		if (line[x] == '\n')
			len = ft_strlen(line) - 1;
		else
			len = ft_strlen(line);
		if (len != x)
			ft_error("Error\nInvalid map: map is not rectangular");
		map[j] = ft_substr(line, 0, x);
		free(line);
		line = get_next_line(fd);
		j++;
	}
	return (map);
}

void	map_check1(t_var	*d)
{
	int	i;
	int	j;

	i = 0;
	d->c = 0;
	d->move = 0;
	j = 0;
	while (j < d->y)
	{
		i = 0;
		while (i < d->x)
		{
			if (d->map[j][i] == 'C')
				d->c++;
			else if (d->map[j][i] != '1' && d->map[j][i] != '0'
			&& d->map[j][i] != 'P' && d->map[j][i] != 'E')
				ft_error("Error\nInvalid map: Undefined element");
			i++;
		}
		j++;
	}
	if (d->c == 0)
		ft_error("Erron\nInvalid map: Invalid number of elements");
}

void	check_borders(t_var	d)
{
	int	i;

	i = 0;
	while (d.map[0] && i < d.x)
	{
		if (d.map[0][i] != '1')
			ft_error("Error\nInvalid map: Invalid borders");
		i++;
	}
	i = 0;
	while (d.map[d.y - 1] && i < d.x)
	{
		if (d.map[d.y - 1][i] != '1')
			ft_error("Error\nInvalid map: Invalid borders");
		i++;
	}
	i = 0;
	while (i < d.y)
	{
		if (d.map[i][0] != '1' || d.map[i][d.x - 1] != '1')
			ft_error("Error\nInvalid map: Invalid borders");
		i++;
	}
}
