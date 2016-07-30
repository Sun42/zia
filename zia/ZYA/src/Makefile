CXX		=	g++

NAME		=	test_rules

DIR_SRC		=	./

SRC		=	$(DIR_SRC)bnf_rules.cpp \
			$(DIR_SRC)ZiaException.cpp


OBJ		=	$(SRC:.cpp=.o)

INCLUDE		=	-I../includes -I/usr/local/boost_1_39_0/

CXXFLAGS	+=	-Wall -Wextra $(INCLUDE)

LIB_BOOST	=	-L/lib/ -lboost_system-gcc43-mt-1_39 -lboost_thread-gcc43-mt -lboost_serialization-gcc43-mt -lboost_filesystem-gcc43-mt

LIB		=	$(LIB_BOOST)

RM		=	rm -rfv


$(NAME)		:	$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LIB) -ldl -rdynamic

all		:	$(NAME)

clean		:
			$(RM) *~ $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
