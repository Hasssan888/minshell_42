CC = cc 

FLAGC = -Wall -Wextra -Werror

NAME = minishell

BONUS = pipex_bonus

SRC = ft_split.c  excute.c utlis.c error.c allcmd.c one_cmd.c get_next_line.c link_list.c main.c open_file.c here_doc.c

SRC_BONUS = b_utilis.c b_utilis_2.c ft_split.c pipex_bonus.c pipex_utilis.c utilis.c error.c get_next_line.c

OBJE = ${SRC:.c=.o}

OBJE_bonus = ${SRC_BONUS:.c=.o}

all : ${NAME}

${NAME} : ${OBJE}
	${CC} ${FLAGC} -o ${NAME} ${OBJE}

${BONUS} : ${OBJE_bonus}
	${CC} ${FLAGC} -o ${BONUS} ${OBJE_bonus}

bonus : ${BONUS}

%.o: %.c
	${CC} ${FLAGC} -c $< -o $@

clean :
	rm -f ${OBJE} ${OBJE_bonus}

fclean : clean
	rm -f $(NAME) ${BONUS}

re: fclean all bonus