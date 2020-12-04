/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:01:09 by asaadi            #+#    #+#             */
/*   Updated: 2020/11/19 13:23:10 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"
#include <math.h>
#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#define SP 100
#define PL 101
#define SQ 102
#define TR 103
#define CY 104
#define ESC 53

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	double x_res;
	double y_res;
	double viewport_height;
	double viewport_width;
	int k;
} t_mlx;

typedef struct s_img
{
	void *img;
	int *addr;
	int bits_per_pixel;
	int size_line;
	int endian;
} t_img;

typedef struct s_coord
{
	double x;
	double y;
	double z;
} t_coord;

typedef struct s_color
{
	double r;
	double g;
	double b;
} t_color;

typedef struct s_camera
{
	t_coord eye;
	t_coord look_at;
	t_coord v_up;
	double fov;
	t_coord w;
	t_coord u;
	t_coord v;
	t_coord centre;
	t_coord lower_left_corner;
	struct s_camera *next;
} t_camera;

typedef struct s_ray
{
	t_coord origin;
	t_coord direction;
} t_ray;

typedef struct s_sphere
{
	t_coord center;
	double radius;
	t_color s_color;
} t_sphere;

typedef struct s_plane
{
	t_coord point_at_pl;
	t_coord plane_norm;
	t_color pl_col;
} t_plane;

typedef struct s_triangle
{
	t_coord first_point;
	t_coord second_point;
	t_coord third_point;
	t_coord norm_tr;
	t_color tr_col;
} t_triangle;

typedef struct s_square
{
	t_coord sq_center;
	t_coord or_vec;
	double size_side;
	t_color sq_col;
	t_coord p1;
	t_coord p2;
	t_coord p3;
	t_coord p4;
} t_square;

typedef struct s_cylinder
{
	t_coord pos;
	t_coord normal;
	double diameter;
	double height;
	t_color col;
} t_cylinder;

typedef struct s_light
{
	t_coord position;
	double kd;
	t_color intensity;
	struct s_light *next;
} t_light;

typedef struct s_illum
{
	t_color amb_col;
	double ka;
} t_illum;

typedef struct s_hit_rec
{
	double t;
	double t_closest;
	double m;
	t_coord hit_point;
	t_coord normal;
	t_coord light_ray;
	t_coord view;
	t_coord refl;
} t_hit_rec;

typedef struct s_objects
{
	t_sphere sphere;
	t_plane plane;
	t_triangle triangle;
	t_square square;
	t_cylinder cylinder;
	int obj_type;
	struct s_objects *next;
} t_objects;

typedef struct s_data
{
	t_objects *objects;
	t_camera *camera;
	t_ray ray;
	t_light *light;
	t_illum illum;
	t_hit_rec rec;
} t_data;

t_coord new_vector(double x, double y, double z);
t_coord sub_vec(t_coord *v1, t_coord *v2);
double vec_dot(t_coord v1, t_coord v2);
t_coord vect_scal(double sca, t_coord vec);
t_coord vec_add(t_coord *v1, t_coord *v2);
t_coord vec_div(t_coord *v1, t_coord *v2);
t_coord vec_div_sca(t_coord v1, double sca);
t_coord vec_cross(t_coord *v1, t_coord *v2);
double lenght(t_coord vec);
t_coord unit_vector(t_coord v);
t_color get_color(double r, double g, double b);
t_color add_color(t_color col1, t_color col2);
t_color sca_div_col(t_color col, double k);
double inters_ray_sphere(t_data *data, t_objects *obect, t_ray *r);
double inters_ray_plan(t_data *data, t_objects *obj, t_ray *r);
double inters_ray_triangle(t_data *data, t_objects *obj, t_ray *ray);
double inters_ray_square(t_data *data, t_objects *obj, t_ray *ray);
double inters_ray_cylinder(t_data *data, t_objects *obj, t_ray *ray);
t_coord point_of_hit(double t, t_ray r);
double ft_strtod(const char *str);
void ft_pars_scene(t_data *data, t_mlx *mlx, char **av);
void parser_resolution(t_mlx *mlx, char *line);
char **ft_split_whitespaces(char *s);
void parser_ambiant_light(t_data *data, char *line);
void parser_light(t_data *data, char *line);
void parser_camera(t_data *data, char *line);
void parser_sphere(t_data *data, char *line);
void parser_plane(t_data *data, char *line);
void parser_square(t_data *data, char *line);
void parser_cylinder(t_data *data, char *line);
void parser_triangle(t_data *data, char *line);
t_color scene_trace(t_data *data);
void min_max_color(t_color *result);
void ft_camera_viewport(t_mlx *mlx, t_data *data);
t_ray get_ray(t_data *data, t_mlx *mlx, int i, int j);
t_color ambient_light(t_data *data);
t_color deffuse_light(t_data *data, t_light *light);
t_color specular_light(t_data *data, t_light *light);

#endif
