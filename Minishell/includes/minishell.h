/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:37:47 by gdilly            #+#    #+#             */
/*   Updated: 2021/08/09 23:37:48 by gdilly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "struct.h"
# include <readline/readline.h>
# include <readline/history.h>

void	ft_start_minishell(void);
void	ft_load_file_history(void);
void	ft_write_history(char *in);
bool	ft_strcompare(const char *s1, const char *s2);
void	ft_print_error_1(char *err_1, char *err_str, int err_code);
void	ft_print_err_2(char *err_1, char *err_2, char *err_str, int err_code);
void	ft_add_str(char **str, char *new_value);
int		ft_len_arr(char **array);
void	ft_arr_free(char **arr);
size_t	ft_find_char(const char *str, char c);
char	*ft_get_path_pwd(void);
int		ft_clean_input(char **in);
void	ft_exec_built(char **argv);
char	*ft_find_env(char *str);
int		ft_check_unset(const char *str);
void	ft_overwrite_env(char *env, char *data);
char	**ft_get_paths(void);
bool	ft_str_isdigit(char *str);
int		ft_return_more_value(int a, int b);
int		ft_check_is_file(char *str, bool should_close);
int		ft_create_new_file(char *str, bool should_close);
int		ft_open_file(char *str);
void	ft_cmds_pwd(void);
void	ft_cmds_echo(char **argv);
void	ft_cmds_exit(char **argv);
void	ft_cmds_export(char **argv);
void	ft_cmds_env(char **argv);
void	ft_cmds_cd(char **argv);
void	ft_cmds_uncet(char **argv);
char	**ft_pars(char *str);
void	ft_update_t_pars_2(char c, t_pars *parsing);
void	ft_add_char(char **str, char c);
void	ft_add_args(char **args, char *str);
void	ft_check_env(char **cmd_arg);
void	ft_check_str_code(char **cmd_arg);
void	ft_check_tilde(char **cmd_arg);
void	ft_delete_backslash(char **cmd_arg);
void	ft_delete_mark(char **cmd_arg);
void	ft_str_replace(char **cmd_arg, \
						unsigned int start_i, unsigned int end_i, char *value);
t_cmds	**ft_get_cmds(char *cmd_str);
void	ft_free_cmd(t_cmds **cmd);
void	ft_exec_cmd(t_cmds	**cmd);
bool	ft_check_cmd(t_cmds	**cmd);
void	ft_exec_pipe(t_cmds **cmd, int *i, int icmd, int ocmd);
void	ft_exec_redir_left_1(t_cmds *cmd1, t_cmds *cmd_file);
void	ft_exec_redir_left_2(t_cmds *cmd1, t_cmds *end_keyword);
void	ft_exec_redir_right_1(t_cmds *cmd1, t_cmds *cmd_file);
void	ft_exec_redir_right_2(t_cmds *cmd1, t_cmds *cmd_file);
bool	ft_check_is_simple(t_cmds **cmd, int *i);
void	ft_exec_redir_left(t_cmds **cmd, int *i);
bool	ft_exec_redir_right(t_cmds **cmd, int *i);
bool	ft_check_is_multi_cmd(t_cmds **cmd, int *save_i, int *fin, int *fout);
void	ft_exec_all_redir(t_cmds *cmd);
void	ft_print_err_code(int code, char *cmd);
void	ft_void_free(void **p);
bool	ft_check_char(char c_1, char c_2, char *set);
bool	ft_ischar(char c, const char *str);
void	ft_sort_tmp(char **tmp_1);
bool	ft_dop_check_av(char **argv);

#endif
