/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:50:50 by lminta            #+#    #+#             */
/*   Updated: 2019/09/04 21:36:17 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WIN_W					m_s->settings.win_w
# define WIN_H					m_s->settings.win_h
# define TOTAL_SURF				256
# define TEX_SIZE				64
# define TICKS_PER_FRAME		25
# define THREADS				m_s->settings.thread

# include <SDL.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <math.h>
# include "get_next_line.h"

enum				e_img_type
{
	FILL,
	OUTLINE,
	ON,
	OFF,
	UP,
	DOWN,
	FULL,
	FOUR
};

typedef struct		s_borders
{
	double			xmin;
	double			ymin;
	double			xmax;
	double			ymax;

}					t_borders;

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
	double			br;
	double			vu_br;
}					t_color;
typedef struct		s_xy
{
	double			x;
	double			y;
	double			intery;
	t_color			color;
}					t_xy;

typedef struct		s_rect
{
	t_xy			xy;
	t_xy			wh;
}					t_rect;

typedef struct		s_player
{
	t_xy			xy;
	double			a;
	double			fov;
	double			vert;
	double			speed;
}					t_player;

typedef struct		s_steep_grad
{
	int				steep;
	double			grad;
}					t_steep_grad;

typedef struct		s_tex
{
	SDL_Surface		*frames[TOTAL_SURF];
	int				len;
	int				freq;
}					t_tex;

typedef struct		s_map
{
	int				map[TOTAL_SURF][TOTAL_SURF];
	int				map_w;
	int				map_h;
}					t_map;

typedef struct		s_monster
{
	double			x;
	double			y;
	int				tex_id;
}					t_monster;

typedef struct		s_settings
{
	char			interlacing;
	char			y_axis;
	int				win_w;
	int				win_h;
	int				distance;
	int				light;
	Uint32			screen;
	int				thread;
	int				tex_mod;
}					t_settings;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*win_surf;
	SDL_Surface		*error_surf;
	SDL_Renderer	*renderer;
	SDL_Event		event;
}					t_sdl;

typedef struct		s_snuffbox
{
	t_settings		settings;
	t_monster		enemys[TOTAL_SURF];
	t_tex			tex[TOTAL_SURF];
	t_color			color;
	t_sdl			sdl;
	t_borders		bd;
	t_map			map;
	t_player		player;
	t_rect			rect;
	unsigned int	step;
	unsigned int	frame;
	unsigned char	running;
}					t_snuffbox;

typedef struct		s_thread
{
	unsigned int	num_thread;
	t_snuffbox		*m_s;
}					t_thread;

int					ipart(double x);
int					ft_round(double x);
double				fpart(double x);
double				rfpart(double x);
void				ft_swap(double *a, double *b);
void				init_win(t_snuffbox *m_s);
void				close_win(t_snuffbox *main_struct);
SDL_Surface			*load_picture(const char *filename);
void				print_error(const char *message, const char *error_message);
void				load_dir(t_snuffbox *m_s, const char *dirname);
SDL_Surface			*opt_surf(t_snuffbox *m_s, SDL_Surface *in);
void				opt_dir(t_snuffbox *m_s);
void				surf_to_text(t_snuffbox *m_s);
void				plot(t_snuffbox *m_s, int x, int y, t_color cl);
void				draw_line(t_snuffbox *m_s, t_xy *xy0, t_xy *xy1);
t_color				gradient(t_color *color1, t_color *color2, double length);
t_color				sum_collors(t_color *color, t_color *grad, int count);
t_color				fill_color(double red, double green,
double blue, double alpha);
void				ft_swap_color(t_color *a, t_color *b);
t_borders			fill_borders(double xmin, double ymin,
double xmax, double ymax);
void				clip(t_snuffbox *m_s, t_xy xy1, t_xy xy2);
t_snuffbox			twist_roll_up(t_snuffbox *m_s, t_borders bd);
void				draw_rect(t_snuffbox *m_s, t_rect rect, int type);
t_rect				fill_rect(t_xy xy, t_xy wh);
t_xy				fill_xy(double x, double y, t_color color);
void				plot_int(t_snuffbox *m_s, int x, int y, int cl);
t_color				int_to_rgb(int	num);
int					*tex_column(t_snuffbox *m_s, int col_h,
int tex_id, int tex_coord);
int					read_map(t_snuffbox *m_s, char *fname);
void				draw_minimap(t_snuffbox *m_s);
void				draw_back(void *data);
int					draw_level(void *data);
void				key_check(t_snuffbox *m_s);
void				put_player(t_snuffbox *m_s);
void				close_wolf(t_snuffbox *m_s, char code);
void				new_win(t_snuffbox *m_s);
int					check_frame(t_snuffbox *m_s);
void				esk_check(t_snuffbox *m_s);
void				f_f(t_snuffbox *m_s, char flag);
void				draw_screen(t_snuffbox *m_s);
void				draw_fill_shade(t_snuffbox *m_s, t_rect *rect, int type);
int					tex_id_check(t_snuffbox *m_s, t_rect *rect);
int					player_check(t_snuffbox *m_s);

#endif
