/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 18:01:38 by lminta            #+#    #+#             */
/*   Updated: 2019/08/30 21:49:35 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "keys.h"

void	key_press(t_snuffbox *m_s)
{
	if (m_s->sdl.event.key.keysym.sym == SDLK_4)
		key_4(m_s);
	else if (m_s->sdl.event.key.keysym.sym == SDLK_z)
		key_z(m_s);
}

void	key_z(t_snuffbox *m_s)
{
	if (m_s->player.speed == 1 / 12.)
		m_s->player.speed = 1 / 6.;
	else
		m_s->player.speed = 1 / 12.;
}

void	key_4(t_snuffbox *m_s)
{
	if (m_s->settings.tex_mod == FULL)
	{
		m_s->settings.tex_mod = FOUR;
		ft_putstr("settings.tex_mod = FOUR");
	}
	else
	{
		m_s->settings.tex_mod = FULL;
		ft_putstr("settings.tex_mod = FULL");
	}
	ft_putchar('\n');
}
