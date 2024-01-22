NAME	=	philo
SRC_DIR	=	./srcs/
INC_DIR	=	./includes/
SRCS	=	main.c\
			parsing.c\
			utils.c\
			init.c\
			philo.c\
			print.c\
			routine.c\
			routine2.c\
			utils2.c\


SRC_BASENAME    =    $(addprefix $(SRC_DIR), $(SRCS))
OBJS            =    $(SRC_BASENAME:.c=.o)
CC				=	gcc
FLAGS			=	-g -Wall -Wextra -Werror -I $(INC_DIR)

.c.o	:
			$(CC) $(FLAGS) -c $< -o $@

all	:		$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean	:
			rm -rf $(OBJS)

fclean	:	clean
			rm -f $(NAME)

fsanitize : $(OBJS)
			$(CC) $(FLAGS) -fsanitize=thread -o $(NAME) $(OBJS)

pthread	:	$(OBJS)
			$(CC) $(FLAGS) -pthread -g -o $(NAME) $(OBJS)

re		:	fclean all

.PHONY	:	all clean fclean re
