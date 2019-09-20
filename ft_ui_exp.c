/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/20 21:15:12 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	void ft_move(t_w *w, int key)
**	Function to move pic with arrows
** **************************************************************************
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
*/

void		ft_change_shape(t_w *w, int key)
{
	if (w->f_type == 1)
	{
		if (key == NUM_6)
			w->j_cre += 0.0002 * (1000 / w->zm);
		if (key == NUM_4)
			w->j_cre -= 0.0002 * (1000 / w->zm);
		if (key == NUM_2)
			w->j_cim += 0.0002 * (1000 / w->zm);
		if (key == NUM_8)
			w->j_cim -= 0.0002 * (1000 / w->zm);
		ft_draw(w);
	}
}

/*
** **************************************************************************
**	void ft_change_color(t_w *w, int key)
**	Function to change color
** **************************************************************************
*/

void		ft_change_color(t_w *w, int key)
{
	if (key == R_KEY)
		w->r_clr += INT32_MAX / 7;
	if (key == G_KEY)
		w->g_clr += INT32_MAX / 7;
	if (key == B_KEY)
		w->b_clr += INT32_MAX / 7;
	if (key == C_KEY)
		w->lsd = 1;
	ft_draw(w);
}

/*
** **************************************************************************
**	static void ft_j_vary(t_w *w, int iter, int x, int y)
**	Function to change Julia vary
** **************************************************************************
*/

static void		ft_j_vary(t_w *w, int *x, int *y)
{
//	double		offs_w;
//	double		offs_h;
	double		offs_x;
	double		offs_y;

	printf("\n-------ft_j_vary start-------\n");
	w->m_x = 1.5 * (w->m_x - W_WIDTH / 2) / (0.5 * w->zm * W_WIDTH) + w->mv_x;
	w->m_y = (w->m_y - W_HEIGHT / 2) / (0.5 * w->zm * W_HEIGHT) + w->mv_y;
	//offs_x = ((W_HEIGHT / 2) - *x);
	//offs_y = (*y - (W_WIDTH / 2));
	offs_x = 1.5 * (*x - W_WIDTH / 2) / (0.5 * w->zm * W_WIDTH) + w->mv_x;
	offs_y = (*y - W_HEIGHT / 2) / (0.5 * w->zm * W_HEIGHT) + w->mv_y;
	offs_x = w->m_x - offs_x;
	offs_y = w->m_y - offs_y;
	printf("offs_x=%f offs_y=%f\n", offs_x, offs_y);
	//w->j_cre -= offs_x * (0.0002 * (10 / w->zm));
	//w->j_cim -= offs_y * (0.0002 * (10 / w->zm));
	w->j_cre += offs_x * (0.0002 / w->zm);
	w->j_cim += offs_y * (0.0002 / w->zm);
	//w->j_cre -= offs_x * (0.0002 / w->zm);
	//w->j_cim -= offs_y * (0.0002 / w->zm);
	/*if (offs_x > 0)
		w->j_cre += offs_x * (0.0002 * (100 / w->zm));
	if (offs_x < 0)
		w->j_cre += offs_x * (0.0002 * (100 / w->zm));
	if (offs_y > 0)
		w->j_cim += offs_y * (0.0002 * (100 / w->zm));
	if (offs_y < 0)
		w->j_cim -= offs_y * (0.0002 * (100 / w->zm));
		*/
	//w->j_cre += (offs_h - offs_y) * (0.0002 * (1000 / w->zm));
	//w->j_cim += (offs_h - offs_y) * (0.0002 * (1000 / w->zm));
	//w->j_cim += offs_y * (0.0002 * (1000 / w->zm));
	//w->j_cre += offs_x * (0.0002 * (1000 / w->zm));
	/*offs_w = 1.5 * (W_WIDTH - W_WIDTH / 2) / (0.5 * w->zm * W_WIDTH) + w->mv_x;
	offs_h = (W_HEIGHT - W_HEIGHT / 2) / (0.5 * w->zm * W_HEIGHT) + w->mv_y;

	offs_x = 1.5 * (*x - W_WIDTH / 2) / (0.5 * w->zm * W_WIDTH) + w->mv_x;
	offs_y = (*y - W_HEIGHT / 2) / (0.5 * w->zm * W_HEIGHT) + w->mv_y;*/
	printf("\n-------ft_j_vary end-------\n");
	
}

int			ft_mouse_mv(int x, int y, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	//printf("x=%d y=%d\n", x, y);
	if (w->f_type == 11)
	{
		ft_j_vary(w, &x, &y);
		ft_draw(w);
	}
	return (0);
}


/*
{cIm += 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_KP8)) {cIm -= 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_KP6)) {cRe += 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_KP4)) {cRe -= 0.0002 * frameTime / zoom;}
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


	int		mouse_move_f(int x, int y, void *param)
{
	t_param		*p;

	p = (t_param*)param;
	if (p->current_fractal == JULIA_MOUSE ||
			p->current_fractal == MULTI_JULIA)
	{
		create_j(param, 1, x, y);
		calc_and_refresh(param);
	}
	return (0);
}

void		calc_and_refresh(t_param *param)
{
	trd_starter(param, param->fractal_func);
	if (param->is_chess == 1)
		chess_scale(param);
	mlx_put_image_to_window(param->mlx_ptr,
			param->win_ptr, param->img_ptr, 0, 0);
	put_info(param);
}

void	chess_scale(t_param *param)
{
	int	x;
	int	y;

	x = 1;
	while (x < WINDOW_WIDTH - 1)
	{
		if (x % 2 == 0)
			y = 1;
		else
			y = 2;
		while (y < WINDOW_HEIGTH - 1)
		{
			biliner_put_4dots(param, x, y);
			y += 2;
		}
		x += 1;
	}
}
 */