/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:00:16 by lminta            #+#    #+#             */
/*   Updated: 2019/08/30 19:55:07 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	parse(t_snuffbox *m_s, char *line)
{
	static int	nb = 1;
	int			i;
	int			j;

	i = -1;
	j = 1;
	while (line[++i] && j <= m_s->map.map_w && nb <= m_s->map.map_h)
	{
		if (line[i] == '*')
			m_s->map.map[nb][j++] = -1;
		if (line[i] == '+')
		{
			m_s->map.map[nb][j] = -1;
			m_s->player.xy = fill_xy(j + 0.5, nb + 0.5, m_s->player.xy.color);
			j++;
		}
		else if (ft_isdigit(line[i]))
		{
			if ((m_s->map.map[nb][j++] = atoi(&line[i])) > TOTAL_SURF)
				m_s->map.map[nb][j++] = TOTAL_SURF - 1;
			while (ft_isdigit(line[i]))
				i++;
		}
	}
	nb++;
}

static int	stage_one(t_snuffbox *m_s, char *fname)
{
	int		fd;
	char	*line;

	if ((fd = open(fname, O_RDONLY)) <= 0)
	{
		perror("Error detected");
		return (0);
	}
	if (!(get_next_line(fd, &line)))
		return (0);
	m_s->map.map_w = ft_atoi(line);
	free(line);
	if (!(get_next_line(fd, &line)))
		return (0);
	m_s->map.map_h = ft_atoi(line);
	free(line);
	if (m_s->map.map_w >= TOTAL_SURF || m_s->map.map_h >= TOTAL_SURF ||
	m_s->map.map_w <= 0 || m_s->map.map_h <= 0)
		return (0);
	return (fd);
}

static int	stage_two(t_snuffbox *m_s, int fd)
{
	int		err;
	char	*line;

	while ((err = get_next_line(fd, &line)) > 0)
	{
		parse(m_s, line);
		free(line);
	}
	free(line);
	if (err < 0)
	{
		perror("Error detected");
		return (0);
	}
	close(fd);
	return (1);
}

int			read_map(t_snuffbox *m_s, char *fname)
{
	int	fd;
	int i;
	int j;

	i = -1;
	while (++i < TOTAL_SURF && (j = -1))
		while (++j < TOTAL_SURF)
			m_s->map.map[i][j] = 0;
	if (!(fd = stage_one(m_s, fname)))
		return (0);
	if (!(stage_two(m_s, fd)))
		return (0);
	if (m_s->map.map[(int)m_s->player.xy.y][(int)m_s->player.xy.x] != -1)
		put_player(m_s);
	m_s->rect = fill_rect(fill_xy(0, 0, fill_color(255, 0, 255, 255)),
	fill_xy(WIN_W / (m_s->map.map_w) / 16, WIN_H / m_s->map.map_h / 9,
	fill_color(255, 0, 255, 255)));
	return (1);
}
