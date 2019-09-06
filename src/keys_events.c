/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 22:18:46 by lminta            #+#    #+#             */
/*   Updated: 2019/08/30 21:52:59 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "keys.h"

void	turn_head(t_snuffbox *m_s, t_player *player)
{
	if (m_s->step % 16 < 8)
	{
		m_s->player.xy.y -= cos(m_s->player.a) * 1 / 100;
		m_s->player.xy.x += sin(m_s->player.a) * 1 / 100;
		if (m_s->step % 32 < 16)
			m_s->player.vert -= 1.5;
		else
			m_s->player.vert += 1.5;
	}
	else
	{
		m_s->player.xy.y += cos(m_s->player.a) * 1 / 100;
		m_s->player.xy.x -= sin(m_s->player.a) * 1 / 100;
		if (m_s->step % 32 >= 16)
			m_s->player.vert -= 1.5;
		else
			m_s->player.vert += 1.5;
	}
	if (player_check(m_s) != -1)
		m_s->player = *player;
}

void	key_w(t_snuffbox *m_s, t_player *player)
{
	turn_head(m_s, player);
	m_s->player.xy.x += cos(m_s->player.a) * m_s->player.speed;
	if (player_check(m_s) != -1)
		m_s->player.xy.x = player->xy.x;
	m_s->player.xy.y += sin(m_s->player.a) * m_s->player.speed;
	if (player_check(m_s) != -1)
		m_s->player.xy.y = player->xy.y;
	m_s->step++;
}

void	key_s(t_snuffbox *m_s, t_player *player)
{
	turn_head(m_s, player);
	m_s->player.xy.x -= cos(m_s->player.a) * m_s->player.speed;
	if (player_check(m_s) != -1)
		m_s->player.xy.x = player->xy.x;
	m_s->player.xy.y -= sin(m_s->player.a) * m_s->player.speed;
	if (player_check(m_s) != -1)
		m_s->player.xy.y = player->xy.y;
	m_s->step++;
}

void	mouse_move(t_snuffbox *m_s)
{
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	m_s->player.a -= (WIN_W / 2 - x) / 1000.;
	if (m_s->player.a > 2 * M_PI)
		m_s->player.a -= 2 * M_PI;
	if (m_s->player.a < 0)
		m_s->player.a += 2 * M_PI;
	if (m_s->settings.y_axis == ON)
	{
		m_s->player.vert += (WIN_H / 2 - y) / 2.5;
		if (m_s->player.vert < -WIN_H / 2)
			m_s->player.vert = -WIN_H / 2;
		if (m_s->player.vert > WIN_H / 2)
			m_s->player.vert = WIN_H / 2;
	}
	SDL_WarpMouseInWindow(m_s->sdl.win, WIN_W / 2, WIN_H / 2);
}

void	key_check(t_snuffbox *m_s)
{
	t_player player;

	while (SDL_PollEvent(&m_s->sdl.event))
	{
		if (m_s->sdl.event.type == SDL_QUIT ||
		(m_s->sdl.event.type == SDL_KEYDOWN &&
		m_s->sdl.event.key.keysym.sym == SDLK_ESCAPE))
			m_s->running = OFF;
		else if (m_s->sdl.event.type == SDL_KEYDOWN)
		{
			player = m_s->player;
			if (m_s->sdl.event.key.keysym.sym == SDLK_a)
				m_s->player.a -= M_PI / 360 * 8;
			else if (m_s->sdl.event.key.keysym.sym == SDLK_d)
				m_s->player.a += M_PI / 360 * 8;
			else if (m_s->sdl.event.key.keysym.sym == SDLK_w)
				key_w(m_s, &player);
			else if (m_s->sdl.event.key.keysym.sym == SDLK_s)
				key_s(m_s, &player);
			else
				key_extra(m_s, &player);
		}
	}
	mouse_move(m_s);
}
