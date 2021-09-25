
typedef struct		s_sxy
{
	double			x;
	double			y;
}					t_sxy;

typedef struct		s_sprites
{
	int				spritenum;
	int				*order;
	double			*dist;
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstartx;
	int				drawstarty;
	int				drawendy;
	int				drawendx;
	int				spritewidth;
	double			*zbuffer;
}					t_sprites;

typedef struct		s_textures
{
	int				texdir;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
}					t_textures;

typedef struct		s_rays
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			raydirx;
	double			raydiry;
	double			camerax;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			movespeed;
	double			rotspeed;
	double			perpwalldist;
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				x;
}					t_rays;

typedef struct		s_mlxdata
{
	void			*mlx_yk;
	void			*mlx_w;
	void			*img;
	void			*img2;
	int				*addr;
	int				bpp;
	int				sizeline;
	int				end;
	int				forward;
	int				back;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
	int				width;
	int				height;
	int				*addr2;
}					t_mlxdata;

typedef struct 		s_cub3d
{
	int				rx;
	int				ry;
	int				i;
	int				f;
	int				c;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
	int				numline;
	int				sizeline;
	char			**map;
	char			player;
	int				dx;
	int				dy;
	int				flag_fc;
	int				save;
	int				screenx;
	int				screeny;
	int				flag_er;
	int				player_check;
	int				empline;
	int				flag_inmap;
	int				at3_sum;
	int				er_map;
}					t_cub3d;

typedef struct		s_all
{
	t_cub3d			d;
	t_mlxdata		texture[5];
	t_mlxdata		mlxdata;
	t_rays			ray;
	t_textures		t;
	t_sprites		s;
	t_sxy			*xy;
}					t_all;

