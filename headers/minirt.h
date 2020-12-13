/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:01:09 by asaadi            #+#    #+#             */
/*   Updated: 2020/12/07 08:35:26 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# define SP 100
# define PL 101
# define SQ 102
# define TR 103
# define CY 104
# define ESC 53
# define NEXT_CAM 45
# define PREV_CAM 35

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	double	x_res;
	double	y_res;
	double	viewport_height;
	double	viewport_width;
}				t_mlx;

typedef struct	s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_coord
{
	double	x;
	double	y;
	double	z;
}				t_coord;

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

typedef struct	s_camera
{
	t_coord				eye;
	t_coord				look_at;
	t_coord				v_up;
	double				fov;
	t_coord				w;
	t_coord				u;
	t_coord				v;
	t_coord				centre;
	t_coord				lower_left_corner;
	struct s_camera		*next;
	struct s_camera		*previous;
}				t_camera;

typedef struct	s_ray
{
	t_coord	origin;
	t_coord	direction;
}				t_ray;

typedef struct	s_sphere
{
	t_coord	center;
	double	radius;
	t_color	s_color;
}				t_sphere;

typedef struct	s_plane
{
	t_coord	point_at_pl;
	t_coord	plane_norm;
	t_color	pl_col;
}				t_plane;

typedef struct	s_triangle
{
	t_coord	first_point;
	t_coord	second_point;
	t_coord	third_point;
	t_coord	norm_tr;
	t_color	tr_col;
}				t_triangle;

typedef struct	s_square
{
	t_coord	sq_center;
	t_coord	or_vec;
	double	size_side;
	t_color	sq_col;
	t_coord	p1;
	t_coord	p2;
	t_coord	p3;
	t_coord	p4;
}				t_square;

typedef struct	s_cylinder
{
	t_coord	pos;
	t_coord	normal;
	double	diameter;
	double	height;
	t_color	col;
}				t_cylinder;

typedef struct	s_light
{
	t_coord			position;
	double			kd;
	t_color			intensity;
	struct s_light	*next;
}				t_light;

typedef struct	s_illum
{
	t_color	amb_col;
	double	ka;
}				t_illum;

typedef struct	s_hit_rec
{
	double	t;
	double	t_closest;
	double	m;
	t_coord	hit_point;
	t_coord	normal;
	t_coord	light_ray;
	t_coord	view;
}				t_hit_rec;

typedef struct	s_objects
{
	t_sphere			sphere;
	t_plane				plane;
	t_triangle			triangle;
	t_square			square;
	t_cylinder			cylinder;
	int					obj_type;
	struct s_objects	*next;
}				t_objects;

typedef struct	s_file_header
{
	char	file_type[2];
	int		file_size;
	int		reversed;
	int		offset_bits;
}				t_file_header;

typedef struct	s_infos_header
{
	int			header_size;
	int			img_width;
	int			img_height;
	short int	planes;
	short int	bits_per_pixel;
	int			compression;
	int			image_size;
	int			x_pixel_per_meter;
	int			y_pixel_per_meter;
	int			colors;
	int			important_colors;
}				t_infos_header;

typedef struct	s_data
{
	t_objects	*objects;
	t_camera	*camera;
	t_ray		ray;
	t_light		*light;
	t_illum		illum;
	t_hit_rec	rec;
	t_mlx		mlx;
	t_img		img;
	t_coord		rotation;
	t_coord		translation;
	int			color[3];
	double		shadow;

}				t_data;

/*
** ********VECTORS_COLORS_CALCULATIONS_FUNCTIONS***********
*/

t_coord			new_vector(double x, double y, double z);
t_coord			sub_vec(t_coord *v1, t_coord *v2);
double			vec_dot(t_coord v1, t_coord v2);
t_coord			vect_scal(double sca, t_coord vec);
t_coord			vec_add(t_coord *v1, t_coord *v2);
t_coord			vec_div(t_coord *v1, t_coord *v2);
t_coord			vec_div_sca(t_coord v1, double sca);
t_coord			vec_cross(t_coord *v1, t_coord *v2);
double			lenght(t_coord vec);
t_coord			unit_vector(t_coord v);
t_color			get_color(double r, double g, double b);
t_color			add_color(t_color col1, t_color col2);
t_color			sca_div_col(t_color col, double k);
void			min_max_color(t_color *result);

/*
** ***********RAY_OBJECTS_INTERSECTIONS********************
*/

double			inters_ray_sphere(t_data *data, t_objects *obect, t_ray *r);
double			inters_ray_plan(t_data *data, t_objects *obj, t_ray *r);
double			inters_ray_triangle(t_data *data, t_objects *obj, t_ray *ray);
double			inters_ray_square(t_data *data, t_objects *obj, t_ray *ray);
double			inters_ray_cylinder(t_data *data, t_objects *obj, t_ray *ray);
t_coord			point_of_hit(double t, t_ray r);
t_objects		*find_the_closest_obj(t_data *data, t_ray *ray, t_objects *obj);
void			calcul_normal_at_hit_point(t_data *data, t_objects *obj);
int				intersection_ray_obj(t_data *data,
		t_objects *tmp_objs, t_ray *ray);

/*
** ***************PPARSING_FUNCTIONS***********************
*/

double			ft_strtod(const char *str);
void			ft_pars_scene(t_data *data, char **av);
void			parser_resolution(t_data *data, char *line);
int				ft_ignore_whitespaces(char *line);
char			*check_spaces_between_comma(char *line);
void			parser_ambiant_light(t_data *data, char *line);
void			parser_light(t_data *data, char *line);
void			parser_camera(t_data *data, char *line);
void			parser_sphere(t_data *data, char *line);
void			parser_plane(t_data *data, char *line);
void			parser_square(t_data *data, char *line);
void			parser_cylinder(t_data *data, char *line);
void			parser_triangle(t_data *data, char *line);
t_coord			parser_vector(char **split);
t_color			parser_color(char **split);
void			ft_put_error(t_data *data, char *str);
void			ft_add_cameras(t_camera **alst, t_camera *new);
void			ft_add_objects(t_objects **alst, t_objects *new);
void			ft_add_lights(t_light **alst, t_light *new);
void			ft_free_split(char **split);
int				ft_count_arguments(char **s);
void			check_parse_color(t_data *data, char **split2);
void			check_coord_normal(t_data *data, char **split);
void			check_coord_vec(t_data *data, char **split);
void			ft_check_scene(t_data *data);
void			ft_free_data_scene(t_data *data);

/*
** *******ROTATION_TRANSLATION_FUNCTIONS*******************
*/

void			check_rotation_translation_in_camera(t_data *data,
		t_camera *cam, char **s_line);
void			check_rotation_translation_objs(t_data *data,
		t_objects *obj, char **s_line);
void			check_translation_light(t_data *data,
		t_light *light, char **s_line);
t_coord			ft_make_rotat(t_coord rot, t_coord normal);
t_coord			ft_make_trans(t_coord pos_to_trans, t_coord translation);

/*
** ***********LIGHTING_COMPT_FUNCTIONS*********************
*/

t_color			ambient_light(t_data *data);
t_color			deffuse_light(t_data *data, t_light *light);
t_color			specular_light(t_data *data, t_light *light,
		double shine_factor);
t_color			color_final_pixel(t_data *data, t_objects *obj,
		t_color deff_col, t_color spec_col);
t_color			get_deffuse_at_point(t_data *data,
		t_light *tmp_light, t_color deff0);
t_color			get_spec_at_point(t_data *data, t_light *tmp_light,
		t_objects *obj, t_color spec0);

/*
** ***********RENDERING_FUNCTIONS**************************
*/

void			trace_ray(t_data *data, t_camera *camera);
t_color			scene_trace(t_data *data);

/*
** ***************GENERATE_RAY_CAMERA_FUNCTIONS************
*/

void			ft_camera_viewport(t_data *data, t_camera *camera);
t_ray			get_ray(t_data *data, t_camera *camera, int i, int j);
void			wich_camera(int button, t_data *data);

/*
** **************CREATE_WINDOW_FUNCTION********************
*/

void			ft_create_the_window(t_data *data, char *name_program);

/*
** ***************CREATE_BMP_FUNCTION**********************
*/

void			ft_create_image_bmp(t_data *data);
void			ft_create_image(t_data *data);

/*
** **************HOOKS*************************************
*/

int				key_press(int button, t_data *data);
int				ft_close(t_data *data);

#endif
