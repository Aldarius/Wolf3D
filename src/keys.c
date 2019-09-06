/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:55:32 by lminta            #+#    #+#             */
/*   Updated: 2019/08/30 15:21:51 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "keys.h"

void		key_kp_plus(t_snuffbox *m_s)
{
	if (m_s->settings.win_w == 1920)
	{
		m_s->settings.screen = SDL_WINDOW_FULLSCREEN_DESKTOP;
		new_win(m_s);
		SDL_GetWindowSize(m_s->sdl.win, &m_s->settings.win_w,
		&m_s->settings.win_h);
	}
	else if (m_s->settings.win_w == 320)
	{
		m_s->settings.win_w = 640;
		m_s->settings.win_h = 360;
	}
	else if (m_s->settings.win_w == 640)
	{
		m_s->settings.win_w = 1280;
		m_s->settings.win_h = 720;
	}
	else if (m_s->settings.win_w == 1280)
	{
		m_s->settings.win_w = 1920;
		m_s->settings.win_h = 1080;
	}
	if (m_s->settings.screen == SDL_WINDOW_ALLOW_HIGHDPI)
		new_win(m_s);
}

void		key_kp_minus(t_snuffbox *m_s)
{
	if (m_s->settings.screen == SDL_WINDOW_FULLSCREEN_DESKTOP)
	{
		m_s->settings.screen = SDL_WINDOW_ALLOW_HIGHDPI;
		m_s->settings.win_w = 1920;
		m_s->settings.win_h = 1080;
	}
	else if (m_s->settings.win_w == 1920)
	{
		m_s->settings.win_w = 1280;
		m_s->settings.win_h = 720;
	}
	else if (m_s->settings.win_w == 1280)
	{
		m_s->settings.win_w = 640;
		m_s->settings.win_h = 360;
	}
	else if (m_s->settings.win_w == 640)
	{
		m_s->settings.win_w = 320;
		m_s->settings.win_h = 180;
		new_win(m_s);
	}
	if (m_s->settings.win_w != 320)
		new_win(m_s);
}

void		esk_check(t_snuffbox *m_s)
{
	while (SDL_PollEvent(&m_s->sdl.event))
	{
		if (m_s->sdl.event.type == SDL_QUIT ||
		(m_s->sdl.event.type == SDL_KEYDOWN &&
		m_s->sdl.event.key.keysym.sym == SDLK_ESCAPE))
			m_s->running = OFF;
	}
}

static void	check_resol(t_snuffbox *m_s)
{
	if (m_s->rect.xy.x <= WIN_W && m_s->rect.xy.y <= WIN_H)
	{
		draw_rect(m_s, m_s->rect, FILL);
		if (m_s->frame % 60 == 0)
			SDL_UpdateWindowSurface(m_s->sdl.win);
	}
}

void		f_f(t_snuffbox *m_s, char flag)
{
	long int		rndval;
	unsigned int	lsb;

	m_s->frame = 0;
	rndval = 1;
	m_s->running = ON;
	if (m_s->settings.interlacing == ON)
		m_s->settings.interlacing = OFF;
	m_s->rect.xy.color = fill_color(152, 0, 2, 255);
	m_s->rect.wh = fill_xy(WIN_W / 320, WIN_H / 180, m_s->rect.xy.color);
	SDL_ShowCursor(SDL_ENABLE);
	while ((rndval != 1 && m_s->running == ON) || flag)
	{
		++m_s->frame;
		flag = 0;
		m_s->rect.xy.y = ((rndval & 0x000FF) - 1) * m_s->rect.wh.y;
		m_s->rect.xy.x = ((rndval & 0x1FF00) >> 8) * m_s->rect.wh.x;
		lsb = rndval & 1;
		rndval >>= 1;
		if (lsb)
			rndval ^= 0x00012000;
		check_resol(m_s);
		esk_check(m_s);
	}
	close_wolf(m_s, 0);
}
