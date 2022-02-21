# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mac <mac@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 14:50:13 by yagnaou           #+#    #+#              #
#    Updated: 2022/02/21 18:39:49 by mac              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c pipex_utils.c pipex_utils2.c

BSCRS = pipex_bonus.c pipex_utils.c pipex_utils2.c

OBJS = $(SRCS:.c=.o)

BOBJS = $(BSCRS:.c=.o)

all : $(NAME)
	$(CC) $(CFLAGS) pipex.c $(NAME) -o pipex

bonus : $(BOBJS)
	$(CC) $(CFLAGS) pipex_bonus.c $(NAME) -o pipex_bonus

$(NAME) : $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<
	ar rc $(NAME) $@

clean :
	@rm -rf $(OBJS) $(BOBJS)

fclean : clean
	@rm -rf $(NAME) $(OBJS) $(BOBJS) pipex pipex_bonus

re : fclean all bonus pipex pipex_bonus