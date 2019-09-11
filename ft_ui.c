/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:32:09 by drafe             #+#    #+#             */
/*   Updated: 2019/09/11 18:55:29 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** **************************************************************************
**	int ft_zoom(int x, int y)
**	Function to  mouse input
** **************************************************************************
*/
static void		ft_zoom(t_w *w, int *x, int *y)
{
	double		old_zm;

	double		offs_x;
	double		offs_y;
	double		dzm;
	
	old_zm = w->zm;
	w->zm *= pow(1.001, 1000);
	dzm = w->zm - old_zm;
	offs_x = 1.5 * (*x - w->width / 2) / (0.5 * old_zm * w->width) + w->mv_x;
	offs_y = (*y - w->height / 2) / (0.5 * old_zm * w->height) + w->mv_y;
	w->mv_x = offs_x;
	w->mv_y = offs_y;
	//w->mv_x = 0.0003 * (offs_x / w->zm);//(offs_x / dzm) - (offs_x / dzm);
	//w->mv_y = 0.0003 * (offs_y / w->zm);//(offs_y / dzm) - (offs_y / dzm);
	printf("x=%f y=%f offs_x=%f offs_y=%f\n",w->mv_x, w->mv_y, offs_x, offs_y);
}
/*	//offs_x = 1.5 * (*x - w->width / 2) / (0.5 * w->zm * w->width) + w->mv_x;
	//offs_y = (*y - w->height / 2) / (0.5 * w->zm * w->height) + w->mv_y;
	b = 1.5 * (w->width - w->width / 2) / (0.5 * w->zm * w->width) + w->mv_x;
	b = (w->height - w->height / 2) / (0.5 * w->zm * w->height) + w->mv_y;
	//if (offs_x > 0)
		//w->mv_x -= offs_x / 2;//(offs_x - a) * (w->zm - 1);//fabs(offs_x)
	//	w->mv_x -= 0.0003 * (1000 / w->zm);
	//if (offs_x < 0)
		//w->mv_x += offs_x / 2;
	//	w->mv_x += 0.0003 * (1000 / w->zm);
	//if (offs_y > 0)
	//	w->mv_y -= offs_y / 2;//(offs_x - a) * (w->zm - 1);//fabs(offs_x)
	//if (offs_y < 0)
	//	w->mv_y += offs_y / 2;
 */
    /* Zoom into the image.
    image.setScaleX(image.getScaleX() * factor);
    image.setScaleY(image.getScaleY() * factor);
    // Calculate displacement of zooming position.
    var dx = (currentMouseX - image.getLeft()) * (factor - 1),
        dy = (currentMouseY - image.getTop()) * (factor - 1);
    // Compensate for displacement.
    image.setLeft(image.getLeft() - dx);
    image.setTop(image.getTop() - dy);
*/
/*
** **************************************************************************
**	int ft_ui_mouse(int key, int x, int y, void *param)
**	Function to handle mouse input
** **************************************************************************
*/

int			ft_ui_mouse(int key, int x, int y, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	ft_putnbr(key);
	if ((key == 1) || (key == 2))// 5 4
	{
		ft_putstr("\nZooming...");
		if (key == 5)
			ft_zoom(w, &x, &y);
		else
			w->zm /= pow(1.001, 1000);
		ft_draw(w);
		printf("%fdone!", w->zm);
	}
	return ((int)param);
}
/*
	//new_w->mv_x += ((new_w->width / (-2)) + x) / (10 * new_w->zm);
	//new_w->mv_y += ((new_w->width / 2) - y) / (10 * new_w->zm);
	//new_w->zm / (new_w->width - y);
    //ZOOM keys
    if(keyDown(SDLK_KP_PLUS))  {zoom *= pow(1.001, 1);}
    if(keyDown(SDLK_KP_MINUS)) {zoom /= pow(1.001, 1);}
    //MOVE keys
    if(keyDown(SDLK_DOWN))  {moveY += 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_UP))  {moveY -= 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_RIGHT)) {moveX += 0.0003 * frameTime / zoom;}
    if(keyDown(SDLK_LEFT))  {moveX -= 0.0003 * frameTime / zoom;}
    //CHANGE SHAPE keys
    if(keyDown(SDLK_KP2)) {cIm += 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_KP8)) {cIm -= 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_KP6)) {cRe += 0.0002 * frameTime / zoom;}
    if(keyDown(SDLK_KP4)) {cRe -= 0.0002 * frameTime / zoom;}
*/

/*
** **************************************************************************
**	int ft_ui_keys(int key, void *param)
**	Function to handle key_input
** **************************************************************************
*/

int		ft_ui_keys(int key, void *param)
{
	t_w		*w;

	w = (t_w*)param;
	ft_putnbr(key);
	if (key == 69)
	{
		w->max_i += 50;
		ft_draw(w);
	}
	if (key == 78)
	{
		w->max_i -= 50;
		ft_draw(w);
	}
	if (key == 49)
	{
		w->max_i = 100;
		ft_init_arr_fractols(w);
		ft_draw(w);
	}
	if (key == 123)
	{
		w->mv_x -= 0.0003 * (1000 / w->zm);//new_w->zm / 10;
		ft_draw(w);
	}
	if (key == 124)
	{
		
		w->mv_x += 0.0003 * (1000 / w->zm);//new_w->zm / 10;//0.1;
		ft_draw(w);
	}
	if (key == 125)
	{
		w->mv_y += w->zm / 10;//0.1;
		ft_draw(w);
	}
	if (key == 126)
	{
		w->mv_y -= w->zm / 10;//0.1;
		ft_draw(w);
	}
	if (key == 53)
		exit(0);
		return ((int)param);
}
/*
** **************************************************************************
**	void ft_ui(t_w *new_w)
**	Function to create win_p
** **************************************************************************
*/

void		ft_ui(t_w *new_w)
{
	printf("\n-------ft_ui start-------\n");
	new_w->win_p = mlx_new_window(new_w->mlx_p, new_w->width, new_w->height, "Fractol");
	ft_putstr("Fractol man:\n\
	ESC : quit Fractol");
	printf("-------ft_ui end-------\n");
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
