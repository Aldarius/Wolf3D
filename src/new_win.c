/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:01:26 by lminta            #+#    #+#             */
/*   Updated: 2019/09/04 21:51:43 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		new_win(t_snuffbox *m_s)
{
	close_win(m_s);
	if (!(m_s->sdl.win =
	SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, m_s->settings.screen)))
	{
		print_error("No window for you: ", SDL_GetError());
		exit(1);
	}
	if (!(m_s->sdl.win_surf = SDL_GetWindowSurface(m_s->sdl.win)))
	{
		print_error("No surface for you: ", SDL_GetError());
		exit(1);
	}
	m_s->rect = fill_rect(fill_xy(0, 0, fill_color(255, 0, 255, 255)),
	fill_xy(WIN_W / (m_s->map.map_w) / 16 * 2, WIN_H / m_s->map.map_h / 9 * 2,
	fill_color(255, 0, 255, 255)));
	SDL_ShowCursor(SDL_DISABLE);
}

void		close_win(t_snuffbox *m_s)
{
	SDL_FreeSurface(m_s->sdl.win_surf);
	SDL_DestroyWindow(m_s->sdl.win);
}

void		draw_screen(t_snuffbox *m_s)
{
	int			k;
	SDL_Thread	*threads[THREADS];
	t_thread	data[THREADS];

	k = 0;
	while (k < THREADS)
	{
		data[k].m_s = m_s;
		data[k].num_thread = k;
		threads[k] = SDL_CreateThread(draw_level, "thread", (void *)(&data[k]));
		++k;
	}
	k = 0;
	while (k < THREADS)
	{
		SDL_WaitThread(threads[k], NULL);
		++k;
	}
	draw_minimap(m_s);
}

void		draw_fill_shade(t_snuffbox *m_s, t_rect *rect, int type)
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
			if (type == UP && m_s->settings.light == ON)
				rect->xy.color.vu_br = ((rect->wh.y - j) /
				(double)WIN_H) * m_s->settings.distance / 10.;
			else if (type == DOWN && m_s->settings.light == ON)
				rect->xy.color.vu_br = j /
				(double)WIN_H * m_s->settings.distance / 10.;
			plot(m_s, rect->xy.x + i, rect->xy.y + j, rect->xy.color);
		}
		if (m_s->settings.interlacing == OFF)
			i++;
		else
			i += 2;
	}
}

int			tex_id_check(t_snuffbox *m_s, t_rect *rect)
{
	t_xy	hitxy;

	if ((rect->xy.intery =
	m_s->map.map[(int)rect->xy.y][(int)rect->xy.x]) == -1)
		return (0);
	if (m_s->settings.tex_mod == FULL)
		return (1);
	else
	{
		hitxy.y = rect->xy.y - floor(rect->xy.y + 0.5);
		hitxy.x = rect->xy.x - floor(rect->xy.x + 0.5);
		if (fabs(hitxy.y) < 0.01 && hitxy.y < 0)
			rect->xy.intery = 11;
		else if (fabs(hitxy.y) < 0.01 && hitxy.y > 0)
			rect->xy.intery = 12;
		else if (fabs(hitxy.x) < 0.01 && hitxy.x < 0)
			rect->xy.intery = 13;
		else if (fabs(hitxy.x) < 0.01 && hitxy.x > 0)
			rect->xy.intery = 14;
	}
	return (1);
}
