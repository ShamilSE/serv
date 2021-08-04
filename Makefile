NAME = webserv
SRC = main.cpp Server/Server.cpp Client/Client.cpp\
	Request/Request.cpp Response/Response.cpp\
	Main/Main.cpp\
	Configuration/Configuration.cpp\
	utils/parser.cpp utils/other.cpp\
	utils/strToMap.cpp\
	utils/split.cpp\
# CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC)
	g++ $(CFLAGS) $(SRC) -o $(NAME) -g

clean:
	rm $(NAME)

re: clean all

.PHONY: all clean re