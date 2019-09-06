/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:32:53 by lminta            #+#    #+#             */
/*   Updated: 2019/08/22 12:33:05 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "keys.h"

void	key_plus(t_snuffbox *m_s)
{
	m_s->settings.distance += 1;
	if (m_s->settings.distance > 100)
		m_s->settings.distance = 100;
	ft_putstr("settings.distance = ");
	ft_putnbr(m_s->settings.distance);
	ft_putchar('\n');
}

void	key_minus(t_snuffbox *m_s)
{
	m_s->settings.distance -= 1;
	if (m_s->settings.distance < 3)
		m_s->settings.distance = 3;
	ft_putstr("settings.distance = ");
	ft_putnbr(m_s->settings.distance);
	ft_putchar('\n');
}

void	key_l(t_snuffbox *m_s)
{
	if (m_s->settings.light == ON)
	{
		m_s->settings.light = OFF;
		ft_putstr("settings.light = OFF");
	}
	else
	{
		m_s->settings.light = ON;
		ft_putstr("settings.light = ON");
	}
	ft_putchar('\n');
}

void	thread_up(t_snuffbox *m_s)
{
	m_s->settings.thread += 1;
	if (m_s->settings.thread > 100)
		m_s->settings.thread = 100;
	ft_putstr("settings.thread = ");
	ft_putnbr(m_s->settings.thread);
	ft_putchar('\n');
}

void	thread_down(t_snuffbox *m_s)
{
	m_s->settings.thread -= 1;
	if (m_s->settings.thread < 1)
		m_s->settings.thread = 1;
	ft_putstr("settings.thread = ");
	ft_putnbr(m_s->settings.thread);
	ft_putchar('\n');
}
