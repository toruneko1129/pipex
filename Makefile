# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 17:06:15 by hkawakit          #+#    #+#              #
#    Updated: 2021/09/24 18:10:47 by hkawakit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
SRCDIR	=	./srcs
SRCLIST	=	main.c \
			error.c
SRCS	=	$(addprefix $(SRCDIR)/, $(SRCLIST))
OBJDIR	=	./objs
OBJS	=	$(SRCLIST:%.c=$(OBJDIR)/%.o)
LIBDIR	=	./libft
LIBFT	=	ft
INCLUDE	=	-I./includes -I$(LIBDIR)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LFLAGS	=	-L$(LIBDIR) -l$(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


$(NAME): $(OBJS)
	make bonus -C $(LIBDIR)
	$(CC) $(CFLAGS) $^ $(INCLUDE) $(LFLAGS) -o $@

all: $(NAME)

clean:
	make clean -C $(LIBDIR)
	rm -rf $(OBJDIR)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
