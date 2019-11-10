/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:56:35 by lminta            #+#    #+#             */
/*   Updated: 2019/10/28 14:04:28 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	nullificator(t_snuffbox *m_s)
{
	int	i;
	int j;

	i = -1;
	while (++i < TOTAL_SURF && (j = -1))
		while (++j < TOTAL_SURF)
		{
			m_s->tex[i].frames[j] = m_s->sdl.error_surf;
			m_s->tex[i].len = 1;
			m_s->tex[i].freq = 1;
		}
	i = -1;
	while (++i < TOTAL_SURF)
		m_s->enemys[i].tex_id = 0;
	SDL_ShowCursor(SDL_DISABLE);
	m_s->frame = 0;
}

static void	init_const(t_snuffbox *m_s)
{
	nullificator(m_s);
	m_s->color = fill_color(255, 255, 255, 255);
	m_s->bd.xmax = WIN_W;
	m_s->bd.xmin = 0;
	m_s->bd.ymax = WIN_H;
	m_s->bd.ymin = 0;
	m_s->player.xy = fill_xy(0, 0, fill_color(255, 255, 255, 255));
	m_s->player.a = 1.5;
	m_s->player.vert = 0;
	m_s->player.fov = M_PI / 3;
	m_s->step = 4;
	m_s->running = ON;
	m_s->settings.thread = 8;
	m_s->settings.interlacing = OFF;
	m_s->settings.light = ON;
	m_s->settings.tex_mod = FULL;
	m_s->settings.screen = SDL_WINDOW_ALLOW_HIGHDPI;
	m_s->settings.y_axis = OFF;
	m_s->settings.distance = 10;
	m_s->player.speed = 1 / 12.0;
	if (!(read_map(m_s, "map")))
		close_wolf(m_s, 1);
}

void		init_win(t_snuffbox *m_s)
{
	m_s->settings.win_h = 360;
	m_s->settings.win_w = 640;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		print_error("No SDL for you: ", SDL_GetError());
		exit(1);
	}
	if (!(m_s->sdl.win =
	SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI)))
	{
		print_error("No window for you: ", SDL_GetError());
		exit(1);
	}
	if (!(m_s->sdl.error_surf = load_picture("res/error.bmp")))
		close_wolf(m_s, 1);
	if (!(m_s->sdl.win_surf = SDL_GetWindowSurface(m_s->sdl.win)))
	{
		print_error("No surface for you: ", SDL_GetError());
		exit(1);
	}
	m_s->sdl.error_surf = opt_surf(m_s, m_s->sdl.error_surf);
	init_const(m_s);
}

void		close_wolf(t_snuffbox *m_s, char code)
{
	int	i;
	int	j;

	SDL_FreeSurface(m_s->sdl.win_surf);
	i = -1;
	while (++i < TOTAL_SURF && (j = -1))
		while (++j < TOTAL_SURF)
			if (m_s->tex[i].frames[j] != m_s->sdl.error_surf &&
			m_s->tex[i].frames[j])
				SDL_FreeSurface(m_s->tex[i].frames[j]);
	i = -1;
	SDL_FreeSurface(m_s->sdl.error_surf);
	SDL_DestroyWindow(m_s->sdl.win);
	SDL_Quit();
	exit(code);
}
