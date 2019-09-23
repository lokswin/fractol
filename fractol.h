/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:45:14 by drafe             #+#    #+#             */
/*   Updated: 2019/09/23 21:47:47 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
#include "./libft/libft.h"
#include "keys.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <pthread.h>
# define W_WIDTH 1348
# define W_HEIGHT 1348

#include <time.h>
//# define ABS(var)((var) < 0 ? -(var) : (var))

/*
** **************************************************************************
**	typedef struct s_w
**	Structure for store window settings
** **************************************************************************
*/

typedef struct		s_w
{
	char			*img;
	int				threads;
	int				flow;
	int				stop;
	int				file_w;
	int				file_h;
	int				file_l;
	double			x_scl;
	double			y_scl;
	double			j_cim;
	double			j_cre;
	int				m_x;
	int				m_y;
	int				last_px;
	int				px;
	int				py;
	int				max_i;
	int				b_clr;
	int				g_clr;
	int				r_clr;
	int				lsd;
	int				ln_sz;
	int				bitspp;
	int				endi;
	int				f_type;
	double			zm;
	double			mv_x;
	double			mv_y;
	double			fractols[5][3];
	void			*mlx_p;
	void			*win_p;
	void			*img_p;
}					t_w;

void				ft_init_arr_fractols(t_w *w);

void				ft_crds_scale(t_w *w, int px, int py);
int					ft_draw(t_w *w);
void				ft_thread_select(void *(*func)(void*), t_w *w);
void				ft_fractol_select(t_w *w, int x, int y);
void				*ft_multi(void *pxl_ptr);
void				*ft_multi2(void *pxl_ptr);

void				ft_mandelbrot(t_w *w, int px, int py);
void				ft_julia(t_w *w, int px, int py);

void				ft_img_pxl_put(t_w *w, int x, int y, int i);
void				ft_draw_man(t_w *w);

void				ft_new_win(t_w *w);
void				ft_w_layout(t_w *w);

void				ft_ui(t_w *w);
int					ft_ui_keys(int key, void *param);
int					ft_ui_mouse(int key, int x, int y, void *param);
int					ft_mouse_mv(int x, int y, void *param);
void				ft_zoom(t_w *w, int *x, int *y);

void				ft_move_shape(t_w *w, int key);
void				ft_change_shape(t_w *w, int key);
void				ft_change_color(t_w *w, int key);


//int					fdf_dw_ln(t_crds *point, t_w new_w, int p1, int p2);
//int					fdf_dw_ln2(t_crds *point, t_w new_w, int p1, int p2);
//int					fdf_draw(t_w *new_w);

//int					fdf_keys(int key, void *param);
//t_w					*fdf_ui(t_w *new_w, int first_time);

//void				fdf_p_struct(t_w *new_w);

//void				fdf_rotate_xy(double *x, double *y, double z, t_w *new_w);
//int					fdf_redraw(t_w *new_w);
//void				fdf_speed_up(t_w *new_w, int parts);

#endif