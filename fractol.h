/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:45:14 by drafe             #+#    #+#             */
/*   Updated: 2019/09/06 18:06:26 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
#include "./libft/libft.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
//# define ABS(var)((var) < 0 ? -(var) : (var))

/*
** **************************************************************************
**	typedef struct s_crds
**	Structure for store point coordinates
** **************************************************************************
*/

typedef struct		s_crds
{
	int				x;
	int				y;
	int				z;
}					t_crds;

/*
** **************************************************************************
**	typedef struct s_w
**	Structure for store window settings
** **************************************************************************
*/

typedef struct		s_w
{
	char			*f_name;
	int				file_w;
	int				file_h;
	int				file_l;
	int				width;
	int				height;
	int				x_mid;
	int				y_mid;
	int				map_ln;
	int				iso_p;
	int				p_nb;
	int				mv;
	double			angle;
	t_list			*all_p;
	t_crds			*p;
	void			*mlx_p;
	void			*win_p;
}					t_w;

t_crds				*fdf_init_one_p(t_w *new_w, char *s, int y);

void				fdf_new_win(t_w *new_w, char *source_f);

int					fdf_dw_ln(t_crds *point, t_w new_w, int p1, int p2);
int					fdf_dw_ln2(t_crds *point, t_w new_w, int p1, int p2);
int					fdf_draw(t_w *new_w);

int					fdf_keys(int key, void *param);
t_w					*fdf_ui(t_w *new_w, int first_time);

void				fdf_p_struct(t_w *new_w);

void				fdf_rotate_xy(double *x, double *y, double z, t_w *new_w);
int					fdf_redraw(t_w *new_w);
void				fdf_speed_up(t_w *new_w, int parts);

#endif