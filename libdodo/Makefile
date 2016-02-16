# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 10:27:09 by dbousque          #+#    #+#              #
#    Updated: 2016/01/02 12:12:13 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libdodo.a

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC=get_next_line.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_strlen.c \
	ft_strdup.c \
	ft_strcpy.c \
	ft_strncpy.c \
	ft_strcat.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_strnstr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strnew.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strsplit.c \
	ft_itoa.c \
	ft_lstaddend.c \
	ft_putstrstr.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putendl.c \
	ft_putnbr.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstadd.c \
	ft_lstdel.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_printf.c \
	ft_ntoa_base.c \
	ft_putaddr.c \
	ft_puthexa.c \
	ft_putlong.c \
	ft_putnbr_un.c \
	ft_putoctal.c \
	ft_putunicode.c \
	ft_unicode_utils.c \
	ft_putwchar.c \
	ft_putwchar2.c \
	ft_putbinary.c \
	ft_putstr_unprint.c \
	color.c \
	get_arg.c \
	parse_format.c \
	get_flags.c \
	print_format.c \
	get_width_n_length.c \
	arg_put.c \
	arg_put2.c \
	arg_put3.c \
	arg_put4.c \
	format_var.c \
	get_precision.c \
	ft_putdouble.c \
	precision.c \
	precision2.c \
	width.c \
	sharp.c \
	utils.c \
	utils2.c

OBJ=$(SRC:.c=.o)

$(NAME): libdodo.h
		$(CC) $(CFLAGS) -c $(SRC)
			ar rc $(NAME) $(OBJ)
				ranlib $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all
