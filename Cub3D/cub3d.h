
#ifndef _CUB3D_H
# define _CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "struct.h"

# define BUF_SIZE	1000

int					ft_cub3d(char *str, t_all *all);
void				ft_pars(char *filemap, t_all *all);
int					ft_map_in_struct(char *filemap, t_all *all, int k);
//int					ft_dot_str(char *str);
int					ft_find_char(char *str, char c);
//int					ft_close_map_ver(char *str);
int					ft_player(char c, t_all *all, int i, int j);
void				ft_res_color_cf(char **str, t_all *all);
int					ft_atoi2(const char *str, t_all *all);
int					ft_atoi3(const char *str, t_all *all);
void				ft_pars_texturs(char *str, t_all *all);
//int					ft_tex_path(char *str, char **texture,
//						t_all *all, int j, int i);
void				ft_initdata(t_all *all);
int					ft_close_map(t_all *all, int i);
int					ft_valid_map(char *str, t_all *all);
void				ft_map_size_num(char *str, t_all *all, int i);
int					ft_cp_map(char *str, t_all *all, int g);
void				ft_num_sprite(t_all *all, int);
int					ft_raycast(t_all *all);
int					ft_mlx_init(t_all *all);
int					ft_press_key(int keycode, t_all *all);
int					ft_release_key(int keycode, t_all *all);
int					ft_color_vertical(t_all *all);
void				ft_text_draw(t_all *all, int x, int y);
void				ft_init_mlx_data(t_all *all);
void				ft_initdata_ray(t_all *all);
void				ft_initdata_texture(t_all *all);
void				ft_num_sprite_more(t_all *all, int i, int j, int v);
void				ft_step_dist_side(t_all *all);
void				ft_inc_ray(t_all *all);
void				ft_draw_start_end(t_all *all);
void				ft_switch(t_all *all);
void				ft_key_w_key_s(t_all *all);
void				ft_key_a_key_d(t_all *all);
void				ft_rot_left_rigth(t_all *all);
void				ft_printerr(t_all *all, char *str);
int					ft_esc_exit(t_all *all, char *str);
void				ft_possible_errors(t_all *all);
void				ft_print_win(t_all *all, int fd);
void				ft_image_save(t_all *all);
void				ft_spr(t_all *all);
int					gnl_mod(int fd, char **line, t_all *all);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_subbuff(char *buff, int start, int len);
void				ft_init_ray_more(t_all *all);
void				ft_rot_left(t_all *all, double olddirx);
void				ft_atoi_er(char *str, t_all *all, int g, int i);
int					ft_lignevide(char *str);
int					ft_saveflag(char *str);
int					ft_com(const char *str);
void				ft_mlx_rx_ry(t_all *all);
int					ft_line_copy(char **line, char **buf);
void				ft_pars_texturs(char *str, t_all *all);
void				ft_read_texture(t_all *all);
int		ft_empline(char *str, int i);





#endif