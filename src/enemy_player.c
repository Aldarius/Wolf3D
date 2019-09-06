/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 11:44:56 by lminta            #+#    #+#             */
/*   Updated: 2019/08/30 15:26:08 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_frame(t_snuffbox *m_s)
{
	if (m_s->frame % 2 || m_s->settings.interlacing == OFF)
		return (0);
	else
		return (1);
}

void	put_player(t_snuffbox *m_s)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 1;
	while (++i <= m_s->map.map_h && !(j = 0))
		while (++j <= m_s->map.map_w)
			if (m_s->map.map[i][j] == -1)
			{
				flag = 0;
				m_s->player.xy =
				fill_xy(j + 0.5, i + 0.5, m_s->player.xy.color);
				return ;
			}
	if (flag)
	{
		print_error("Ну ты и долбаеб братишка\n", "Земля тебе пухом");
		close_wolf(m_s, 1);
	}
}

int		player_check(t_snuffbox *m_s)
{
	t_xy	xy;

	xy = m_s->player.xy;
	if (m_s->map.map[(int)xy.y][(int)xy.x] != -1 ||
	m_s->map.map[(int)(xy.y + 0.1)][(int)xy.x] != -1 ||
	m_s->map.map[(int)(xy.y + 0.1)][(int)(xy.x + 0.1)] != -1 ||
	m_s->map.map[(int)(xy.y)][(int)(xy.x + 0.1)] != -1 ||
	m_s->map.map[(int)(xy.y - 0.1)][(int)xy.x] != -1 ||
	m_s->map.map[(int)(xy.y - 0.1)][(int)(xy.x - 0.1)] != -1 ||
	m_s->map.map[(int)(xy.y)][(int)(xy.x - 0.1)] != -1 ||
	m_s->map.map[(int)(xy.y - 0.1)][(int)(xy.x + 0.1)] != -1 ||
	m_s->map.map[(int)(xy.y + 0.1)][(int)(xy.x - 0.1)] != -1)
		return (0);
	return (-1);
}
