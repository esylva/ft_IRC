# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esylva <esylva@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 12:52:36 by esylva            #+#    #+#              #
#    Updated: 2022/05/04 12:53:29 by esylva           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := bur
 
SRCS := main.cpp
# OBJS := ${patsubst %.cpp,%.o,${SRCS}}
# D_FILES := ${patsubst %.cpp,%.d,${SRCS}}

GCC := c++

# FLAGS := -Wall -Wextra -Werror -std=c++98 -Wshadow

all: ${NAME}

${NAME}: 
	${GCC} ${FLAGS} ${SRCS} -o ${NAME}
	./bur

# ${NAME} : ${OBJS}
# 	${GCC} ${OBJS} -o ${NAME}

# %.o : %.cpp
# 	${GCC} ${FLAGS} -c $< -o $@ -MD

include ${wildcard ${D_FILES}}

clean:
	rm -rf ${OBJS} ${D_FILES}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re