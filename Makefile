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
BUILD_DIR = build/

SRCS = 	srcs/main.cpp \
		$(SERVER)server.cpp \
		$(CLIENT)client.cpp 

OBJS = $(SRCS:%.cpp=$(BUILD_DIR)%.o)
INCLUDES = -I./includes

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)[Linking]$(RESET) Creating executable: $(NAME)"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "\n$(GREEN)[Build complete]$(RESET) $(NAME) is ready !\n"

$(BUILD_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(BLUE)[Compiling]$(RESET) $<"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	clear
	@echo "$(RED)[Cleaning]$(RESET) Removing object files"
	rm -rf $(BUILD_DIR)

fclean: clean
	@echo "$(RED)[Cleaning]$(RESET) Removing executable: $(NAME)"
	rm -f $(NAME)

re: fclean all

run: re
	@echo "$(YELLOW)[Running]$(RESET) Executing $(NAME) on port 6667"
	./$(NAME) 6667

valgrind: re
	@echo "$(YELLOW)[Valgrind]$(RESET) Running memory analysis with Valgrind"
	valgrind --leak-check=full ./$(NAME) 6667


# Special rules
.PHONY: all clean fclean re run valgrind
