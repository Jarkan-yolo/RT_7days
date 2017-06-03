/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltesson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 17:43:10 by ltesson           #+#    #+#             */
/*   Updated: 2017/05/16 16:44:05 by ltesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

static int	expose_hook(t_env *e)
{
	int		bpp;
	int		sl;
	int		endian;

	e->img = mlx_new_image(e->mlx, e->s->cam->xres, e->s->cam->yres);
	e->addr = mlx_get_data_addr(e->img, &bpp, &sl, &endian);
	ft_drawscene(e->s, e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
	return (0);
}

static int	key_hook(int keycode, t_env *e)
{
	if (keycode == 53)
		exit(0);
	if (ft_move(keycode, e->s->cam))
	{
		ft_initcam(e->s->cam);
		expose_hook(e);
	}
	return (0);
}

void		ft_mlx(t_scene *s)
{
	t_env	*e;

	e = (t_env*)malloc(sizeof(t_env));
	e->s = s;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, s->cam->xres, s->cam->yres, "test");
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_key_hook(e->win, key_hook, e);
	mlx_loop(e->mlx);
}
