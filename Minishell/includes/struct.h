/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:37:28 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:37:37 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_global
{
	char	**env;
	int		code;
}			t_global;

t_global	g_global;

typedef struct s_cmds
{
	int		fd_in;
	int		fd_out;
	int		spec;
	char	*str;
	char	**argv;
}				t_cmds;

typedef struct s_pars
{
	bool	mark_1;
	bool	mark_2;
	bool	flag_1;
	bool	flag_2;
	bool	space;
	bool	check_mark;
	bool	dop_flag;
}				t_pars;

typedef struct s_pipe
{
	int		fd_in;
	int		fd_out;
	bool	flag;
	int		std_in;
	int		std_out;
	int		pipes[2];
}				t_pipe;

typedef struct s_exp
{
	char	*tmp;
	int		i;
	int		j;
	int		ac;
}			t_exp;

#endif
