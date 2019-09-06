/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:30:39 by lminta            #+#    #+#             */
/*   Updated: 2019/08/30 21:53:30 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# include "wolf3d.h"

void	key_z(t_snuffbox *m_s);
void	key_4(t_snuffbox *m_s);
void	key_l(t_snuffbox *m_s);
void	key_kp_plus(t_snuffbox *m_s);
void	key_kp_minus(t_snuffbox *m_s);
void	key_plus(t_snuffbox *m_s);
void	key_minus(t_snuffbox *m_s);
void	key_w(t_snuffbox *m_s, t_player *player);
void	key_s(t_snuffbox *m_s, t_player *player);
void	key_q(t_snuffbox *m_s, t_player *player);
void	key_e(t_snuffbox *m_s, t_player *player);
void	key_i(t_snuffbox *m_s);
void	key_y(t_snuffbox *m_s);
void	mouse_move(t_snuffbox *m_s);
void	key_extra(t_snuffbox *m_s, t_player *player);
void	turn_head(t_snuffbox *m_s, t_player *player);
void	thread_down(t_snuffbox *m_s);
void	thread_up(t_snuffbox *m_s);
void	key_press(t_snuffbox *m_s);

#endif
