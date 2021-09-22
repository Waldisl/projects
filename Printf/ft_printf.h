/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:19:55 by msunspot          #+#    #+#             */
/*   Updated: 2021/01/24 13:33:59 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_param
{
	int				i;
	int				minus;
	int				zero;
	int				dot;
	int				width;
	int				precision;
	char			type;
}					t_param;

t_param			ft_parser(char *format, va_list ar);
void				ft_type_proc(t_param par, int *length);
void				ft_type_p(t_param par, va_list ar, int *length);
void				ft_type_x(t_param par, va_list ar, int *length);
void				ft_type_u(t_param par, va_list ar, int *length);
void				ft_type_d_i(t_param par, va_list ar, int *length);
void				ft_type_c(t_param par, va_list ar, int *length);
void				ft_type_s(t_param par, va_list ar, int *length);
void				ft_hex16(size_t num, size_t reg, int *length);
int					ft_length_hex16(size_t number);
int					ft_length_prec(int len, int precision);
void				ft_parser_precision(char *fmt, va_list ar, t_param *par);
void				ft_width(t_param *par, char *fmt);
void				ft_precision(t_param *par, char *fmt);
void				ft_type(t_param *par, char *format);
void				ft_param(char *fmt, va_list ar, t_param *par);
void				print_len(char c, int *length);
int					ft_type_poz(const char *s, int i);
void				ft_vtype(t_param par, va_list ar, int *length);
void				ft_processor(const char *s, va_list ar, int *length);
int					ft_printf(const char *s, ...);

#endif
