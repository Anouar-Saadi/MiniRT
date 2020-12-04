# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/18 15:19:58 by asaadi            #+#    #+#              #
#    Updated: 2020/11/26 10:41:20 by asaadi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CFLAGS = -Wall -Wextra -Werror

#INC_MLX = -I /usr/local/include

#LIB_MLX = -L /usr/local/lib/ -lmlx


MMS_PATH = ./minilibx_mms
OGL_PATH = ./minilibx_opengl

FRAM = -framework OpenGL -framework AppKit
SRC_PATH= src
SRC_NAME =	main.c\
		vectors_operations.c\
		vectors_operations_1.c\
		colors_operations.c\
		parsing.c\
		ft_split_whitespaces.c\
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
		light_illumination.c\
		parse_elements.c

HDR_PATH= headers
HDR_INC= -I ./headers/
LIBFT = libft/libft.a

HDR_NAME = minirt.h mlx.h

OBJ_PATH= objs
OBJ_NAME= $(SRC_NAME:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

all: libft ogl mms $(NAME)

$(NAME): $(OBJ)
	@cp ./minilibx_mms/libmlx.dylib 
	gcc $(CFLAGS) $(OBJ) $(LIBFT) -L $(MMS_PATH) libmlx.dylib $(FRAM) -o $(NAME)
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
	@gcc $(CFLAGE) $(HDR_INC) -o $@ -c $<

ogl:
	@make -sC $(OGL_PATH)

mms:
	@make -sC $(MMS_PATH)
libft:
	@make -sC libft

clean:
	@rm -rf $(OBJ)
	@make -sC clean libft
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "miniRT : Removing Objs"

fclean: clean
	@rm -rf $(NAME)
	@rm -f libmlx.dylib
	@make -sC $(OGL_PATH) clean
	@make -sC $(MMS_PATH) clean
	@echo "miniRT : Removing miniRT"
		
re: fclean all
