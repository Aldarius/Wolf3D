/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:46:18 by lminta            #+#    #+#             */
/*   Updated: 2019/08/21 10:43:35 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_xy	h_end(t_snuffbox *m_s, t_xy *xy, t_steep_grad *sg)
{
	t_xy	end;
	t_xy	pxl;
	double	xgap;

	end.x = ft_round(xy->x);
	end.y = xy->y + sg->grad * (end.x - xy->x);
	xgap = rfpart(xy->x + 0.5);
	pxl.x = (int)end.x;
	pxl.y = ipart(end.y);
	xy->color.vu_br = rfpart(end.y) * xgap;
	if (sg->steep)
	{
		plot(m_s, pxl.y, pxl.x, xy->color);
		xy->color.vu_br = fpart(end.y) * xgap;
		plot(m_s, pxl.y + 1, pxl.x, xy->color);
	}
	else
	{
		plot(m_s, pxl.x, pxl.y, xy->color);
		xy->color.vu_br = fpart(end.y) * xgap;
		plot(m_s, pxl.x, pxl.y + 1, xy->color);
	}
	pxl.intery = end.y + sg->grad;
	pxl.color = xy->color;
	return (pxl);
}

static void	boring_function(t_snuffbox *m_s, t_xy *pxl1,
t_steep_grad *sg, int x)
{
	pxl1->color.vu_br = rfpart(pxl1->intery);
	plot(m_s, ipart(pxl1->intery), x, pxl1->color);
	pxl1->color.vu_br = fpart(pxl1->intery);
	plot(m_s, ipart(pxl1->intery) + 1, x, pxl1->color);
	pxl1->intery = pxl1->intery + sg->grad;
}

static void	another_boring_function(t_snuffbox *m_s,
t_xy *pxl1, t_steep_grad *sg, int x)
{
	pxl1->color.vu_br = rfpart(pxl1->intery);
	plot(m_s, x, ipart(pxl1->intery), pxl1->color);
	pxl1->color.vu_br = fpart(pxl1->intery);
	plot(m_s, x, ipart(pxl1->intery) + 1, pxl1->color);
	pxl1->intery = pxl1->intery + sg->grad;
}

static void	draw_while(t_snuffbox *m_s, t_xy *pxl1,
t_xy *pxl2, t_steep_grad *sg)
{
	int		x;
	t_color	gr;

	x = pxl1->x + 1;
	gr = gradient(&pxl1->color, &pxl2->color, pxl2->x - pxl1->x);
	if (sg->steep)
		while (x < pxl2->x)
		{
			pxl1->color = sum_collors(&pxl1->color, &gr, 1);
			boring_function(m_s, pxl1, sg, x);
			x++;
		}
	else
		while (x < pxl2->x)
		{
			pxl1->color = sum_collors(&pxl1->color, &gr, 1);
			another_boring_function(m_s, pxl1, sg, x);
			x++;
		}
}

void		draw_line(t_snuffbox *m_s, t_xy *xy0, t_xy *xy1)
{
	t_xy			d;
	t_steep_grad	sg;
	t_xy			pxl1;
	t_xy			pxl2;

	sg.steep = fabs(xy1->y - xy0->y) > fabs(xy1->x - xy0->x);
	if (sg.steep)
	{
		ft_swap(&(xy0->x), &(xy0->y));
		ft_swap(&(xy1->x), &(xy1->y));
	}
	if (xy0->x > xy1->x)
	{
		ft_swap(&(xy0->x), &(xy1->x));
		ft_swap(&(xy0->y), &(xy1->y));
		ft_swap_color(&(xy0->color), &(xy1->color));
	}
	d.y = xy1->y - xy0->y;
	if (!(d.x = xy1->x - xy0->x))
		sg.grad = 1.0;
	else
		sg.grad = d.y / d.x;
	pxl1 = h_end(m_s, xy0, &sg);
	pxl2 = h_end(m_s, xy1, &sg);
	draw_while(m_s, &pxl1, &pxl2, &sg);
}
