/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/18 20:59:40 by drafe            ###   ########.fr       */
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
	if (key == ARROW_L)
		w->mv_x -= 0.0003 * (1000 / w->zm);
	if (key == ARROW_R)
		w->mv_x += 0.0003 * (1000 / w->zm);
	if (key == ARROW_D)
		w->mv_y += 0.0003 * (1000 / w->zm);
	if (key == ARROW_U)
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
	if (key == NUM_6)
		w->x_scl += 0.0002 * (1000 / w->zm);
	if (key == NUM_4)
		w->x_scl -= 0.0002 * (1000 / w->zm);
	if (key == NUM_2)
		w->y_scl += 0.0002 * (1000 / w->zm);
	if (key == NUM_8)
		w->y_scl -= 0.0002 * (1000 / w->zm);
	//ft_draw(w);
}


void		ft_change_color(t_w *w, int key)
{
	if (key == R_KEY)
		w->r_clr += 500000;
	if (key == G_KEY)
		w->g_clr += 50000;
	if (key == B_KEY)
		w->b_clr += 50000;
	ft_draw(w);
}

static void		ft_j_vary(t_w *w, int iter, int x, int y)
{
	w->j_iter *= iter;
	//w->x_scl += 0.0002 * (1000 / w->zm);
	w->j_cIm = ((W_WIDTH / 2) - x) / w->j_iter;
	w->j_cRe = (y - (W_HEIGHT / 2)) / w->j_iter;
}

int			ft_mouse_mv(int x, int y, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	printf("x=%d y=%d\n", x, y);
	if (w->f_type == 11)
	{
		ft_j_vary(w, 1, x, y);
		ft_draw(w);
	}
	return (0);
}


/*
void			create_j(t_param *param,
		long double mult, long double x, long double y)
{
	param->mult = param->mult * mult;
	param->julia_x = ((param->start_x) - x) / param->mult;
	param->julia_y = (y - (param->start_y)) / param->mult;
}start_x = W_he/2

void			print_j(t_param *param,
		long double mult, long double x, long double y)
{
	long double		res1;
	long double		res2;

	res1 = (param->j_start_x - x) * mult;
	res2 = (param->j_start_y - y) * mult;
	param->j_start_x = x + res1;
	param->j_start_y = y + res2;
	param->j_mult = param->j_mult * mult;
 */