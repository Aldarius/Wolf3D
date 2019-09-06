/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:30:08 by lminta            #+#    #+#             */
/*   Updated: 2019/08/30 21:40:57 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "keys.h"

void	key_q(t_snuffbox *m_s, t_player *player)
{
	m_s->player.xy.x += sin(m_s->player.a) * 1 / 12;
	if (player_check(m_s) != -1)
		m_s->player.xy.x = player->xy.x;
	m_s->player.xy.y -= cos(m_s->player.a) * 1 / 12;
	if (player_check(m_s) != -1)
		m_s->player.xy.y = player->xy.y;
}

void	key_e(t_snuffbox *m_s, t_player *player)
{
	m_s->player.xy.x -= sin(m_s->player.a) * 1 / 12;
	if (player_check(m_s) != -1)
		m_s->player.xy.x = player->xy.x;
	m_s->player.xy.y += cos(m_s->player.a) * 1 / 12;
	if (player_check(m_s) != -1)
		m_s->player.xy.y = player->xy.y;
}

void	key_i(t_snuffbox *m_s)
{
	if (m_s->settings.interlacing == ON)
	{
		m_s->settings.interlacing = OFF;
		ft_putstr("settings.interlacing = OFF");
	}
	else
	{
		m_s->settings.interlacing = ON;
		ft_putstr("settings.interlacing = ON");
	}
	ft_putchar('\n');
}

void	key_y(t_snuffbox *m_s)
{
	if (m_s->settings.y_axis == ON)
	{
		m_s->settings.y_axis = OFF;
		m_s->player.vert = 0;
		ft_putstr("settings.y_axis = OFF");
	}
	else
	{
		m_s->settings.y_axis = ON;
		ft_putstr("settings.y_axis = ON");
	}
	ft_putchar('\n');
}

void	key_extra(t_snuffbox *m_s, t_player *player)
{
	if (m_s->sdl.event.key.keysym.sym == SDLK_q)
		key_q(m_s, player);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_e)
		key_e(m_s, player);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_i)
		key_i(m_s);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_y)
		key_y(m_s);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_KP_PLUS)
		key_kp_plus(m_s);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_KP_MINUS)
		key_kp_minus(m_s);
	else if (m_s->sdl.event.key.keysym.sym == 61)
		key_plus(m_s);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_MINUS)
		key_minus(m_s);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_l)
		key_l(m_s);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_PERIOD)
		thread_up(m_s);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_COMMA)
		thread_down(m_s);
	else
		key_press(m_s);
}
