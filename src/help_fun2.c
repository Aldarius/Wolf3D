/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:38:06 by lminta            #+#    #+#             */
/*   Updated: 2019/08/15 22:51:01 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_swap_color(t_color *a, t_color *b)
{
	t_color buff;

	buff = *a;
	*a = *b;
	*b = buff;
}

t_borders	fill_borders(double xmin, double ymin, double xmax, double ymax)
{
	t_borders borders;

	borders.xmin = xmin;
	borders.ymin = ymin;
	borders.xmax = xmax;
	borders.ymax = ymax;
	return (borders);
}

t_snuffbox	twist_roll_up(t_snuffbox *m_s, t_borders bd)
{
	t_snuffbox roll_up;

	roll_up = *m_s;
	roll_up.bd = bd;
	return (roll_up);
}

t_xy		fill_xy(double x, double y, t_color color)
{
	t_xy	xy;

	xy.x = x;
	xy.y = y;
	xy.color = color;
	return (xy);
}

void		plot_int(t_snuffbox *m_s, int x, int y, int cl)
{
	int		i;

	if (x > WIN_W || y > WIN_H || x < 0 || y < 0)
		return ;
	i = x + y * WIN_W;
	((int *)(m_s->sdl.win_surf->pixels))[i] = cl;
}
