/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_surf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:18:43 by lminta            #+#    #+#             */
/*   Updated: 2019/09/05 06:27:45 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface	*load_picture(const char *filename)
{
	SDL_Surface	*surf;

	if (!(surf = SDL_LoadBMP(filename)))
		print_error(filename, SDL_GetError());
	return (surf);
}

SDL_Surface	*opt_surf(t_snuffbox *m_s, SDL_Surface *in)
{
	SDL_Surface	*opt;

	if (!in)
		return (0);
	if (!(opt = SDL_ConvertSurface(in, m_s->sdl.win_surf->format, 0)))
	{
		print_error("No optimization for you:", SDL_GetError());
		close_wolf(m_s, 1);
	}
	SDL_FreeSurface(in);
	return (opt);
}

static t_xy	parse_num(char *name)
{
	t_xy	i;

	i.x = ft_atoi(name);
	while (ft_isdigit(*name) && *name)
		name++;
	while (!ft_isdigit(*name) && *name)
		name++;
	i.y = ft_atoi(name);
	while (ft_isdigit(*name) && *name)
		name++;
	while (!ft_isdigit(*name) && *name)
		name++;
	i.intery = ft_atoi(name);
	return (i);
}

void		load_dir(t_snuffbox *m_s, const char *dirname)
{
	struct dirent	*name_buff;
	char			*buff;
	DIR				*res;
	t_xy			i;

	if (!(res = opendir(dirname)))
		close_wolf(m_s, 1);
	while ((name_buff = readdir(res)))
		if (name_buff->d_type == 8)
		{
			buff = ft_strjoin(dirname, name_buff->d_name);
			i = parse_num(name_buff->d_name);
			if (m_s->tex[(int)i.x].frames[(int)i.y] == m_s->sdl.error_surf)
				if (!(m_s->tex[(int)i.x].frames[(int)i.y] = load_picture(buff)))
					m_s->tex[(int)i.x].frames[(int)i.y] = m_s->sdl.error_surf;
			if ((int)i.y == 0)
				m_s->tex[(int)i.x].freq = i.intery;
			if (m_s->tex[(int)i.x].frames[(int)i.y] != m_s->sdl.error_surf &&
			(int)i.y + 1 > m_s->tex[(int)i.x].len)
				m_s->tex[(int)i.x].len = (int)i.y + 1;
			free(buff);
		}
	closedir(res);
}

void		opt_dir(t_snuffbox *m_s)
{
	int	i;
	int j;

	i = -1;
	while (++i < TOTAL_SURF && (j = -1))
		while (++j < TOTAL_SURF)
		{
			if (m_s->tex[i].frames[j] != m_s->sdl.error_surf)
				m_s->tex[i].frames[j] = opt_surf(m_s, m_s->tex[i].frames[j]);
		}
}
