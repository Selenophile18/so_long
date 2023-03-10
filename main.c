/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:26:17 by hhattaki          #+#    #+#             */
/*   Updated: 2023/01/01 21:23:26 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long_bonus.h"

int	ft_key(int key, t_var *d)
{
	if (key == 53)
		exit(0);
	if (key == 13 || key == 126)
		up(d);
	if (key == 1 || key == 125)
		down(d);
	if (key == 2 || key == 124)
		right(d);
	if (key == 0 || key == 123)
		left(d);
	return (d->x);
}

int	destroy(t_var	*d)
{
	mlx_destroy_window(d->mlxp, d->window);
	exit(0);
	return (0);
}

int	rendering(t_var	*d)
{
	int		i;
	int		j;

	j = 0;
	while (j < d->y)
	{
		i = 0;
		while (d->map[j][i])
		{
			print_move(d);
			if (d->map[j][i] == '1')
				wall(d, j, i);
			if (d->map[j][i] == 'C')
				coll(d, j, i);
			if (d->map[j][i] == 'E')
				portal(d, j, i);
			if (d->map[j][i] == 'P')
				player(d, j, i);
			if (d->map[j][i] == '0')
				grass(d, j, i);
			i++;
		}
		j++;
	}
	return (0);
}

int	main(int ac, char	**av)
{
	t_var	d;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (ac != 2 || fd == -1 || !check_arg(av[1]))
		ft_error("Error\nInvalid arguments");
	d.x = get_x(av[1]);
	d.y = get_y(av[1]);
	d.i = 0;
	d.tmr = 0;
	d.map = get_map(fd, d.y, d.x);
	map_check1(&d);
	map_check2(&d);
	check_borders(d);
	final_path(d);
	close(fd);
	d.mlxp = mlx_init();
	d.window = mlx_new_window(d.mlxp, (d.x * 50), (d.y * 50), "so_long");
	mlx_hook(d.window, 17, 0, destroy, &d);
	mlx_loop_hook(d.mlxp, &rendering, &d);
	mlx_key_hook(d.window, &ft_key, &d);
	mlx_loop(d.mlxp);
}
