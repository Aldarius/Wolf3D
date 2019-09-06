/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 20:28:10 by lminta            #+#    #+#             */
/*   Updated: 2019/09/04 21:36:32 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_back(void *data)
{
	int			k;
	int			i;
	t_snuffbox	*m_s;
	t_color		buff;

	m_s = ((t_thread *)data)->m_s;
	k = ((t_thread *)data)->num_thread;
	i = WIN_W / THREADS;
	buff = fill_color(200, 200, 200, 255);
	draw_rect(m_s, fill_rect(fill_xy(i * k, 0, buff),
	fill_xy(i, WIN_H / 2 + m_s->player.vert, buff)), UP);
	buff = fill_color(153, 123, 112, 255);
	draw_rect(m_s, fill_rect(fill_xy(i * k, WIN_H / 2 + m_s->player.vert,
	buff), fill_xy(i, WIN_H / 2 - m_s->player.vert, buff)), DOWN);
}

void		draw_minimap(t_snuffbox *m_s)
{
	int		j;
	int		i;
	int		k;
	int		buff;

	j = 0;
	while (++j <= m_s->map.map_h && !(i = 0))
		while (++i <= m_s->map.map_w)
		{
			if ((buff = m_s->map.map[j][i]) == -1)
				continue;
			m_s->rect.xy.x = i * m_s->rect.wh.x;
			m_s->rect.xy.y = j * m_s->rect.wh.y;
			k = (m_s->frame / m_s->tex[buff].freq) %
			m_s->tex[buff].len;
			m_s->rect.xy.color = int_to_rgb(((int *)
m_s->tex[buff].frames[k]->pixels)[TEX_SIZE / 2 + TEX_SIZE * TEX_SIZE / 2]);
			draw_rect(m_s, m_s->rect, FILL);
		}
	draw_rect(m_s, fill_rect(fill_xy(m_s->player.xy.x * m_s->rect.wh.x - 2.5,
	m_s->player.xy.y * m_s->rect.wh.y - 2.5,
	m_s->color), fill_xy(5, 5, m_s->color)), FILL);
}

static void	draw_level3(t_snuffbox *m_s, int i, int col_h, t_rect cord)
{
	int		*col;
	int		x_tex;
	int		j;
	t_color	buff;

	j = -1;
	if (fabs(cord.xy.y - floor(cord.xy.y + 0.5)) >
	fabs(cord.xy.x - floor(cord.xy.x + 0.5)))
		x_tex = (cord.xy.y - floor(cord.xy.y + 0.5)) * TEX_SIZE;
	else
		x_tex = (cord.xy.x - floor(cord.xy.x + 0.5)) * TEX_SIZE;
	if (x_tex < 0)
		x_tex += TEX_SIZE;
	col = tex_column(m_s, col_h, cord.xy.intery, x_tex);
	cord.wh.x = 0 + i;
	while (++j < col_h)
	{
		cord.wh.y = j + m_s->player.vert + WIN_H / 2 - col_h / 2;
		if (cord.wh.y < 0 || cord.wh.y >= WIN_H)
			continue;
		buff = int_to_rgb(col[j]);
		buff.vu_br = cord.xy.color.vu_br;
		plot(m_s, cord.wh.x, cord.wh.y, buff);
	}
	free(col);
}

static void	draw_level2(t_snuffbox *m_s, int i, double angle)
{
	double	t;
	t_rect	cord;

	t = 0;
	while (t < m_s->settings.distance)
	{
		cord.xy.x = m_s->player.xy.x + t * cos(angle);
		cord.xy.y = m_s->player.xy.y + t * sin(angle);
		cord.wh.x = cord.xy.x * m_s->rect.wh.x;
		cord.wh.y = cord.xy.y * m_s->rect.wh.y;
		if ((cord.xy.color.vu_br = 1) && m_s->settings.light == ON)
			cord.xy.color.vu_br = 1 - t / m_s->settings.distance;
		cord.xy.color.vu_br *= cord.xy.color.vu_br;
		m_s->player.xy.color.vu_br = cord.xy.color.vu_br;
		plot(m_s, cord.wh.x, cord.wh.y, m_s->player.xy.color);
		if (tex_id_check(m_s, &cord))
		{
			draw_level3(m_s, i, (WIN_H) /
			(t * cos(angle - m_s->player.a)), cord);
			break ;
		}
		t += 0.01;
	}
}

int			draw_level(void *data)
{
	int			i;
	int			k;
	t_snuffbox	*m_s;
	double		angle;

	draw_back(data);
	m_s = ((t_thread *)data)->m_s;
	k = ((t_thread *)data)->num_thread;
	i = check_frame(m_s) + (WIN_W / THREADS) * k;
	while (i < (WIN_W / THREADS) * (k + 1))
	{
		angle = m_s->player.a - m_s->player.fov / 2 +
		m_s->player.fov * i / ((double)WIN_W);
		draw_level2(m_s, i, angle);
		if (m_s->settings.interlacing == OFF)
			i++;
		else
			i += 2;
	}
	return (0);
}
