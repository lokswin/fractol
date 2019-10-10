/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:45:14 by drafe             #+#    #+#             */
/*   Updated: 2019/10/10 22:06:43 by drafe            ###   ########.fr       */
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
#include <time.h>
# define W_WIDTH 800
# define W_HEIGHT 800

//# define ABS(var)((var) < 0 ? -(var) : (var))

/*
** **************************************************************************
**	typedef struct s_w
**	Structure for store window settings
** **************************************************************************
*/

typedef struct		s_w
{
	pthread_mutex_t lock_x;
	char			*img;
	int				threads;
	double			cycle;
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

typedef struct		s_fractol
{
	double			re;
	double			im;
	double			x;
	double			y;
}					t_fractol;

typedef struct		s_param
{
	int				py_beg;
	int				py_end;
	t_w				*w;
}					t_param;

void				ft_init_arr_fractols(t_w *w);
void				ft_putman(void);

void				ft_crds_scale(t_w *w, int px, int py);
int					ft_draw(t_w *w);
void				ft_thread_select(void *(*func)(void*), t_w *w);
void				*ft_fractol_select(void *w_ptr);
void				*ft_multi(void *pxl_ptr);
void				*ft_multi2(void *pxl_ptr);

void				ft_mand(t_param *p);
void				ft_julia(t_param *p);
void				ft_carpet(t_param *p);
void				ft_self_call(t_param *p);
void				ft_sierpinski(t_param *p);
void				ft_burning_ship(t_param *p);
void				ft_rand_walk(t_param *p);
void				ft_henon(t_param *p);

void				ft_img_pxl_put(t_w *w, int x, int y, int i);
void				ft_draw_iter(t_w *w);

void				ft_new_win(t_w *w);
void				ft_w_layout(t_w *w);

void				ft_ui();
int					ft_keyrelease(int key, t_w *w);
int					ft_ui_keys(int key, void *param);
int					ft_ui_mouse(int key, int x, int y, void *param);
int					ft_mouse_mv(int x, int y, void *param);
void				ft_zoom(t_w *w, int *x, int *y);

void				ft_move_sh(t_w *w, int key);
void				ft_change_sh(t_w *w, int key);
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