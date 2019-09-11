/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/11 21:23:57 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	void ft_move(t_w *w, int key)
**	Function to move pic with arrows
** **************************************************************************
    //MOVE keys
    if(keyDown(SDLK_DOWN))  {moveY += 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_UP))  {moveY -= 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_RIGHT)) {moveX += 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_LEFT))  {moveX -= 0.0003 * frameTime / zoom;}
*/

void		ft_move_shape(t_w *w, int key)
{
	if (key == 123)
		w->mv_x -= 0.0003 * (1000 / w->zm);
	if (key == 124)
		w->mv_x += 0.0003 * (1000 / w->zm);
	if (key == 125)
		w->mv_y += 0.0003 * (1000 / w->zm);
	if (key == 126)
		w->mv_y -= 0.0003 * (1000 / w->zm);
	ft_draw(w);
}

/*
** **************************************************************************
**	void ft_change_shape(t_w *w, int key)
**	Function to change pic with keys
** **************************************************************************
    //CHANGE SHAPE keys
    if(keyDown(SDLK_KP2)) {cIm += 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_KP8)) {cIm -= 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_KP6)) {cRe += 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_KP4)) {cRe -= 0.0002 * frameTime / zoom;}
*/

void		ft_change_shape(t_w *w, int key)
{
	if (key == 88)
		w->x_scl += 0.0002 * (1000 / w->zm);
	if (key == 86)
		w->x_scl -= 0.0002 * (1000 / w->zm);
	if (key == 84)
		w->y_scl += 0.0002 * (1000 / w->zm);
	if (key == 91)
		w->y_scl -= 0.0002 * (1000 / w->zm);
	//ft_draw(w);
}


void		ft_change_color(t_w *w, int key)
{
	if (key == 15)
		w->r_clr += 500000;
	if (key == 5)
		w->g_clr += 50000;
	if (key == 11)
		w->b_clr += 50000;
	ft_draw(w);
}
/*
** **************************************************************************
**	man /usr/share/man/man3/mlx.1
**	man /usr/share/man/man3/mlx_loop.1
**	man /usr/share/man/man3/mlx_new_image.1
**	man /usr/share/man/man3/mlx_new_window.1
**	man /usr/share/man/man3/mlx_pixel_put.1
** **************************************************************************
*/
