NAME    := a.out
CXX     := clang++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++17 -g

SRCS    := Game.cpp Board.cpp Player.cpp Cpu.cpp main.cpp
OBJS    := $(SRCS:.cpp=.o)

all     : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	./$(NAME)

.PHONY: debug
debug: CXXFLAGS += -pedantic -g -fsanitize=address
debug: re

.PHONY  : all clean fclean re debug
.PHONY: test
