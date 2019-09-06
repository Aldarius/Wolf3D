/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:29:10 by lminta            #+#    #+#             */
/*   Updated: 2019/08/29 14:55:45 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_rect		fill_rect(t_xy xy, t_xy wh)
{
	t_rect	result;

	result.xy = xy;
	result.wh = wh;
	return (result);
}

static void	draw_fill(t_snuffbox *m_s, t_rect *rect)
{
	int		i;
	int		j;

	i = check_frame(m_s);
	while (i < rect->wh.x && (j = -1))
	{
		while (++j < rect->wh.y)
		{
			if (rect->xy.x + i >= WIN_W || rect->xy.y + j >= WIN_H)
				continue ;
			plot(m_s, rect->xy.x + i, rect->xy.y + j, rect->xy.color);
		}
		if (m_s->settings.interlacing == OFF)
			i++;
		else
			i += 2;
	}
}

static void	draw_outline(t_snuffbox *m_s, t_rect *rect)
{
	t_xy	buff1;
	t_xy	buff2;
	t_color	grad;

	buff2.x = rect->xy.x + rect->wh.x;
	buff2.y = rect->xy.y + rect->wh.y;
	buff2.color = rect->wh.color;
	buff1 = rect->xy;
	grad = gradient(&rect->xy.color, &rect->wh.color, 2);
	buff1.color = sum_collors(&buff1.color, &grad, 1);
	buff1.x += rect->wh.x;
	clip(m_s, rect->xy, buff1);
	clip(m_s, buff1, buff2);
	buff1.x -= rect->wh.x;
	buff1.y += rect->wh.y;
	clip(m_s, rect->xy, buff1);
	clip(m_s, buff1, buff2);
}

void		draw_rect(t_snuffbox *m_s, t_rect rect, int type)
{
	if (type == FILL)
		draw_fill(m_s, &rect);
	else if (type == OUTLINE)
		draw_outline(m_s, &rect);
	else if (type == UP)
		draw_fill_shade(m_s, &rect, type);
	else if (type == DOWN)
		draw_fill_shade(m_s, &rect, type);
}

int			*tex_column(t_snuffbox *m_s, int col_h, int tex_id, int tex_coord)
{
	int	*col;
	int	y;
	int	k;
	int	pix_y;

	if (!(col = (int *)malloc(sizeof(int) * col_h)))
		return (0);
	y = -1;
	while (++y < col_h)
	{
		k = (m_s->frame / m_s->tex[tex_id].freq) % m_s->tex[tex_id].len;
		pix_y = y * TEX_SIZE / (double)col_h;
		col[y] =
((int *)m_s->tex[tex_id].frames[k]->pixels)[tex_coord + pix_y * TEX_SIZE];
	}
	return (col);
}
