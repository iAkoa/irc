NAME = ircserv
EXT = cpp
H_EXT = hpp
SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = main.cpp  CSockets.cpp Channel.cpp User.cpp Server.cpp Message.cpp Nick.cpp Join.cpp Topic.cpp Invite.cpp Kick.cpp Mode.cpp Part.cpp Pass.cpp UserCmd.cpp Privmsg.cpp Notice.cpp
SRC = $(SRC_FILES:%.${EXT}=${SRC_DIR}/%.${EXT})
OBJ = $(SRC:${SRC_DIR}/%.${EXT}=${OBJ_DIR}/%.o)
HEADER_DIR = header
HEADER_FILES = CSockets.hpp Channel.hpp User.hpp Server.hpp Message.hpp DMap.hpp DMap.tpp
HEADER = $(HEADER_FILES:%=${HEADER_DIR}/%)
# FLAGS = -Wall -Wextra -Werror -fsanitize=address -std=c++98

all : ${NAME}

${NAME} : ${OBJ}
	c++ $(FLAGS) $(OBJ) ${LIBFT} -o $(NAME)

${OBJ_DIR}/%.o : ${SRC_DIR}/%.${EXT} ${HEADER} | ${OBJ_DIR}
	c++ $(FLAGS) -I ${HEADER_DIR} -c $< -o $@

FORCE :

${OBJ_DIR} :
	mkdir $@

clean :
	rm -rf ${OBJ_DIR}

fclean : 
	rm -f ${NAME}
	rm -rf ${OBJ_DIR}

re : fclean
	make all

.PHONY : clean fclean re FORCE
