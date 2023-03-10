/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:29:43 by hhattaki          #+#    #+#             */
/*   Updated: 2023/01/01 21:16:33 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long_bonus.h"

void	ft_free(char **temp, int y)
{
	int	i;

	i = 0;
	while (i <= y)
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

void	find_pos(int *pos, t_var d)
{
	int	i;
	int	j;

	j = 0;
	pos[0] = 0;
	pos[1] = 0;
	while (j < d.y)
	{
		i = 0;
		while (i < d.x)
		{
			if (d.map[j][i] == 'P')
			{
				pos[0] = j;
				pos[1] = i;
			}
			i++;
		}
		j++;
	}
}

char	**temp_map(t_var	d)
{
	char	**temp;
	int		i;

	temp = ft_calloc(d.y + 2, sizeof(char *));
	i = 0;
	while (i < d.y)
	{
		temp[i] = ft_strdup(d.map[i]);
		i++;
	}
	return (temp);
}

t_path	*check_path(int x, int y, char **map, t_path *checker)
{
	if (y <= 0 && x <= 0)
		return (checker);
	if (map[y][x] == '1')
		return (checker);
	if (map[y][x] == 'N')
		return (checker);
	if (map[y][x] == 'C')
		checker->c_nbr += 1;
	else if (map[y][x] == 'E')
	{
		checker->e = 1;
		return (checker);
	}
	map[y][x] = 'N';
	if (map[y + 1][x] != '1')
		check_path(x, y + 1, map, checker);
	if (map[y - 1][x] != '1')
		check_path(x, y - 1, map, checker);
	if (map[y][x + 1] != '1')
		check_path(x + 1, y, map, checker);
	if (map[y][x - 1] != '1')
		check_path(x - 1, y, map, checker);
	return (checker);
}

void	final_path(t_var	d)
{
	char	**temp;
	t_path	*checker;
	int		pos[2];

	temp = temp_map(d);
	find_pos(pos, d);
	checker = (t_path *) ft_calloc(1, sizeof(t_path));
	checker->e = 0;
	checker->c_nbr = 0;
	checker = check_path(pos[1], pos[0], temp, checker);
	ft_free(temp, d.y);
	if (checker->e == 0)
	{
		free(checker);
		ft_error("Error\nInvalid path: Couldn't reach exit");
	}
	if (checker->c_nbr != d.c)
	{
		free(checker);
		ft_error("Error\nInvalid path: Couldn't reach all collectibles");
	}
	free(checker);
}
