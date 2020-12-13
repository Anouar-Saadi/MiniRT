NAME = miniRT

FLAGS = -Wall -Wextra -Werror

FRAM = -framework OpenGL -framework AppKit

SRC_PATH = srcs

SRC_NAME =  main.c\
			rendering_file.c\
			vectors_operations.c\
			vectors_operations_1.c\
			colors_operations.c\
			colors_operations_1.c\
			parsing.c\
			parsing_1.c\
			get_next_line.c\
			get_next_line_utils.c\
			ft_strtod.c\
			camera.c\
			intersections.c\
			intersection_spheres.c\
			intersection_plans.c\
			intersection_squares.c\
			intersection_triangles.c\
			intersection_cylinders.c\
			get_color_pixels.c\
			get_color_pixels_1.c\
			light_illumination.c\
			parse_elements.c\
			parse_objects.c\
			parse_objects_1.c\
			error.c\
			no_leak.c\
			list_stock.c\
			rotation.c\
			check_rotation_trans.c\
			translation.c\
			make_image_bmp.c\

HDR_PATH = headers/
HDR_INC = -I ./headers
HDR_NAME = minirt.h mlx.h libft.h

OBJ_PATH= objs
OBJ_NAME = $(SRC_NAME:.c=.o)

MMS_PATH = ./minilibx_mms
OGL_PATH = ./minilibx_opengl
LIBFT_PATH = ./libft

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

all: $(NAME) 

$(NAME): $(OBJ)
	@make -sC $(LIBFT_PATH)
	@make -sC $(OGL_PATH)
	@make -sC $(MMS_PATH)
	@cp ./minilibx_mms/libmlx.dylib .
	@cp ./minilibx_opengl/libmlx.a .
	@cp libft/libft.a .
	@gcc $(FLAGS) libmlx.a libmlx.dylib libft.a $(FRAM) $(OBJ) -o $(NAME)
	@echo "\033[1;36m"
	@echo "   ****             *****      *      ***        *      *     ***********       ***********     \n"
	@echo "  |*| \*\          /*/ |*|    |*|    |*|\*\     |*|    |*|   |*|        \*\         |*|         \n"
	@echo "  |*|  \*\        /*/  |*|    |*|    |*| \*\    |*|    |*|   |*|        /*/         |*|         \n"
	@echo "  |*|   \*\      /*/   |*|    |*|    |*|  \*\   |*|    |*|   |*|*********           |*|         \n"
	@echo "  |*|    \*\    /*/    |*|    |*|    |*|   \*\  |*|    |*|   |*|     \*\            |*|         \n"
	@echo "  |*|     \*\  /*/     |*|    |*|    |*|    \*\ |*|    |*|   |*|      \*\           |*|         \n"
	@echo "   *        ****        *      *      *       ***       *     *        **            *          \n"
	@echo "\033[0m"
	@echo "								Created by:"
	@echo "\033[1;30m"
	@echo "									 ASAADI\n"
	@echo "\033[0m"
	@echo "\033[0;33m"
	@echo "			COMPILATION DONE!\n"
	@echo "\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc $(FLAGS) $(HDR_INC)  -o $@ -c $<

clean:
	@rm -rf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@make clean -sC $(LIBFT_PATH)
	@echo "miniRT : Removing Objs"

fclean: clean
	@rm -rf $(NAME)
	@rm -f libmlx.dylib
	@make clean -sC $(OGL_PATH)
	@make clean -sC $(MMS_PATH)
	@rm -f libmlx.a
	@rm -rf libft.a
	@make fclean -sC $(LIBFT_PATH)
	@echo "miniRT : Removing miniRT"

re: fclean all