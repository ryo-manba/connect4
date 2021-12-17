NAME     = connect4
CXX      = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -g -O0 $(INC)

SRCDIR  = ./srcs/
INCDIR  = ./includes
OBJDIR  = ./objs/

SRCNAME   = Game.cpp Board.cpp Player.cpp Cpu.cpp main.cpp
SRCS	= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS	= $(addprefix $(OBJDIR), $(notdir $(SRCS:.cpp=.o)))
INC		= -I $(INCDIR)
RM		= rm -rf

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p objs

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJDIR)

re: fclean all

test: $(NAME)
	./$(NAME)

.PHONY  : all clean fclean re debug
.PHONY: test
