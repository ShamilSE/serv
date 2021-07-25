NAME = webserv
SRC = main.cpp Socket/Socket.cpp Router/Router.cpp HtmlHandler/HtmlHandler.cpp
# CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC)
	g++ $(CFLAGS) $(SRC) -o $(NAME) -g

clean:
	rm $(NAME)

re: clean all

.PHONY: all clean re