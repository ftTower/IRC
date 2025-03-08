.SILENT:

# Colors
RESET = \033[0m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RED = \033[31m

# Variables
NAME = irc

# Flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -Isrcs/server/includes -std=c++98 -g
LDFLAGS =

# Paths
SERVER = srcs/server/
CLIENT = srcs/client/
CHANNEL = srcs/channel/
CMD = srcs/commands/

BUILD_DIR = build/

SRCS = 	srcs/main.cpp \
		$(SERVER)Server.cpp \
		$(SERVER)serverToClients.cpp \
		$(SERVER)serverToChannels.cpp \
		$(SERVER)serverOutput.cpp \
		$(SERVER)serverGetters.cpp \
		$(SERVER)serverMethods.cpp \
		$(SERVER)serverUtils.cpp \
		$(CLIENT)Client.cpp \
		$(CLIENT)clientSetters.cpp \
		$(CLIENT)clientGetters.cpp \
		$(CLIENT)clientMethods.cpp \
		$(CHANNEL)Channel.cpp \
		$(CHANNEL)channelGetters.cpp \
		$(CHANNEL)channelMethods.cpp \
		$(CMD)cmdParser.cpp \
		$(CMD)Commands.cpp \

OBJS = $(SRCS:%.cpp=$(BUILD_DIR)%.o)
INCLUDES = -I./includes

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo 
	@echo "$(YELLOW) [Linking  ]$(RESET) Creating executable: $(NAME)"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo 
	@echo "$(GREEN) [Built    ] $(NAME)$(RESET) is ready !"
	@echo 

$(BUILD_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(BLUE) [Compiling]$(RESET) $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	clear
	@echo 
	@echo "$(RED) [Cleaning ]$(RESET) Removing object files"
	rm -rf $(BUILD_DIR)

fclean: clean
	@echo "$(RED) [Cleaning ]$(RESET) Removing executable: $(NAME)"
	@echo 
	rm -f $(NAME)

re: fclean all

run: re
	@echo "$(YELLOW) [Running  ]$(RESET) Executing $(NAME) on port 6667"
	@echo 
	./$(NAME) 6667
	make fclean
	
pass: re
	@echo "$(YELLOW) [Running  ]$(RESET) Executing $(NAME) on port 6667"
	@echo 
	./$(NAME) 6667 mdp
	make fclean

valgrind: re
	@echo "$(YELLOW) [Valgrind]$(RESET) Running memory analysis with Valgrind"
	valgrind --leak-check=full ./$(NAME) 6667 
	make fclean

# Special rules
.PHONY: all clean fclean re run valgrind
