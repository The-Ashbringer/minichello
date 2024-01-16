# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 14:13:52 by dcarenou          #+#    #+#              #
#    Updated: 2023/02/28 13:54:49 by dcarenou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_isalpha.c \
		  ft_isdigit.c \
		  ft_memset.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isprint.c \
		  ft_strlen.c \
		  ft_bzero.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_strchr.c \
		  ft_strchri.c \
		  ft_strrchr.c \
		  ft_strncmp.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strnstr.c \
		  ft_atoi.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_striteri.c \
		  ft_itoa.c \
		  ft_substr.c \
		  ft_strmapi.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstsize.c \
		  ft_lstlast.c \
		  ft_lstadd_back.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c \
		  ft_int.c \
		  ft_char.c \
		  ft_hexa.c \
		  ft_pointer.c \
		  ft_printf.c \
		  get_next_line.c \
		  

OBJS	= $(SRCS:.c=.o)

CC		= @gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

NAME	= libft.a

RED		=	\033[1;31m
GRE		=	\033[1;32m
GRA		=	\033[37m
BLU		=	\033[34m
EOC		=	\033[0m
NNE		=	\033[A\033[0m

#rules
all :  $(NAME)
	@echo "██╗░░░░░██╗██████╗░███████╗████████╗"
	@echo "██║░░░░░██║██╔══██╗██╔════╝╚══██╔══╝"
	@echo "██║░░░░░██║██████╦╝█████╗░░░░░██║░░░"
	@echo "██║░░░░░██║██╔══██╗██╔══╝░░░░░██║░░░"
	@echo "███████╗██║██████╦╝██║░░░░░░░░██║░░░"
	@echo "╚══════╝╚═╝╚═════╝░╚═╝░░░░░░░░╚═╝░░░"

%.o : %.c
	@echo "$(GRE)Compiling : $<                                                   $(NNE)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GRE)Compilation of LIBFT is finished."

clean :
	@$(RM) $(OBJS)
	@echo "$(RED)Cleaning of LIBFT is finished."

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
