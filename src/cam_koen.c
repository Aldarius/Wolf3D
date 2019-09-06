/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_koen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 20:42:51 by lminta            #+#    #+#             */
/*   Updated: 2019/07/31 19:43:31 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	code(t_borders *bd, t_xy *xy)
{
	return ((xy->x < bd->xmin) << 3 | (xy->x > bd->xmax) << 2 |
	(xy->y < bd->ymin) << 1 | (xy->y > bd->ymax));
}

static int	new_point(t_borders *bd, t_xy *xy, t_xy *dxy)
{
	if (xy->x < bd->xmin)
	{
		xy->y += dxy->y * (bd->xmin - xy->x) / dxy->x;
		xy->x = bd->xmin;
	}
	else if (xy->x > bd->xmax)
	{
		xy->y += dxy->y * (bd->xmax - xy->x) / dxy->x;
		xy->x = bd->xmax;
	}
	else if (xy->y < bd->ymin)
	{
		xy->x += dxy->x * (bd->ymin - xy->y) / dxy->y;
		xy->y = bd->ymin;
	}
	else if (xy->y > bd->ymax)
	{
		xy->x += dxy->x * (bd->ymax - xy->y) / dxy->y;
		xy->y = bd->ymax;
	}
	return (code(bd, xy));
}

void		clip(t_snuffbox *m_s, t_xy xy1, t_xy xy2)
{
	int		c1;
	int		c2;
	t_xy	dxy;

	c1 = code(&m_s->bd, &xy1);
	c2 = code(&m_s->bd, &xy2);
	while (c1 | c2)
	{
		if (c1 & c2)
			return ;
		dxy.x = xy2.x - xy1.x;
		dxy.y = xy2.y - xy1.y;
		if (c1)
			c1 = new_point(&m_s->bd, &xy1, &dxy);
		else
			c2 = new_point(&m_s->bd, &xy2, &dxy);
	}
	draw_line(m_s, &xy1, &xy2);
}
