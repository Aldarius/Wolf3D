/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:00:37 by lminta            #+#    #+#             */
/*   Updated: 2019/09/05 06:23:21 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_color		int_to_rgb(int num)
{
	t_color	rgb;

	rgb.vu_br = 1;
	rgb.b = num & 255;
	rgb.g = (num >> 8) & 255;
	rgb.r = (num >> 16) & 255;
	rgb.br = (num >> 24) & 255;
	return (rgb);
}

int			main(void)
{
	t_snuffbox	m_s;
	Uint32		time;

	init_win(&m_s);
	load_dir(&m_s, "res/BMP_surf/");
	load_dir(&m_s, "res/BMP_surf/15_0_0/");
	opt_dir(&m_s);
	while (m_s.running == ON)
	{
		time = SDL_GetTicks();
		key_check(&m_s);
		draw_screen(&m_s);
		SDL_UpdateWindowSurface(m_s.sdl.win);
		time = SDL_GetTicks() - time;
		if (time < TICKS_PER_FRAME)
			SDL_Delay(TICKS_PER_FRAME - time);
		m_s.frame++;
	}
	f_f(&m_s, 1);
	return (0);
}
