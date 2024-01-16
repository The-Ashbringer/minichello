# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/22 17:29:03 by dcarenou          #+#    #+#              #
#    Updated: 2023/12/27 00:43:12 by dcarenou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c \
				lexer/lexer.c

OBJS		= $(SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

LIBFT 		= libft/libft.a

RM			= rm -rf

NAME		= minishell

RED			=	\033[1;31m
GRE			=	\033[1;32m
GRA			=	\033[37m
BLU			=	\033[34m
EOC			=	\033[0m
NNE			=	\033[A\033[0m

#rules
all : $(NAME)

%.o : %.c
	@echo "$(GRE)Compiling : $<                                                   $(GRA)$(NNE)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS) $(LIBFT)
	@echo "$(GRE)Compilation of Minishell is finished. $(GRA)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT) :
	@make -C libft/

clean :
	@echo "$(RED)Cleaning of Minishell is finished."
	@$(RM) $(OBJS)
	@make clean -C libft/

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re : fclean all

.PHONY : all clean fclean re