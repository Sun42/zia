CXX		=	g++

NAME		=	server

DIR_SRC		=	./src/

SRC		=	$(DIR_SRC)main.cpp		\
			$(DIR_SRC)Connection.cpp	\
			$(DIR_SRC)Server.cpp

OBJ		=	$(SRC:.cpp=.o)

INCLUDE		=	-I./includes -I/usr/local/boost_1_39_0/

CXXFLAGS	+=	-Wall -Wextra $(INCLUDE)

LIB		=	-L/lib/ -lboost_system-gcc43-mt-1_39 -lboost_thread-gcc43-mt

RM		=	rm -rfv


$(NAME)		:	$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LIB)

all		:	$(NAME)

clean		:
			$(RM) *~ $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
