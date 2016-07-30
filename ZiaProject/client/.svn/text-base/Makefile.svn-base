CXX		=	g++

NAME		=	client

SRC		=	client.cpp

OBJ		=	$(SRC:.cpp=.o)

INCLUDE		=	-I/usr/local/boost_1_40_0/

CXXFLAGS	+=	-Wall -Wextra $(INCLUDE)

LIB		=	-L/usr/local/lib/ -lboost_system

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
