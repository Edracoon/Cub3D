CFLAGS = -Wall -Wextra -Werror -g -I

LIB_DIR = /usr/local/include

SRCS =	main.c get_map_data.c get_map_data_utils.c get_map_data_utils_two.c \
		parse_map.c minilibx.c key_management.c raycasting.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		libft/ft_atoi.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_isalnum.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strlcat.c \
		libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_memset.c libft/ft_strlcpy.c libft/ft_bzero.c \
		libft/ft_memcpy.c libft/ft_memccpy.c libft/ft_calloc.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memmove.c libft/ft_putchar.c libft/ft_putnbr.c libft/ft_putstr.c \
		libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putnbr_fd.c libft/ft_putendl_fd.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_itoa.c libft/ft_split.c \
		libft/ft_strcat.c libft/ft_strcpy.c libft/ft_strtrim.c libft/ft_strmapi.c \

compile:
			#gcc -Wall -Wextra -Werror -L/usr/lib $(SRCS) -Iminilibx_linux -lm
			gcc $(CFLAGS) $(LIB_DIR) $(SRCS) -L minilibx -lmlx -framework OpenGL -framework Appkit

all:		compile

clean:
			rm -f a.out

norme:
			norminette $(SRCS)

re:			clean all
