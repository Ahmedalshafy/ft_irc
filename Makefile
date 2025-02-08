# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmed <ahmed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 23:41:54 by alsaeed           #+#    #+#              #
#    Updated: 2025/02/08 13:29:22 by ahmed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 #-g3 -fsanitize=address
INCLUDES = -IIncludes/

SRCS =  Server.cpp \
        Channel.cpp \
        Client.cpp \
        ParseMessage.cpp \
        quit.cpp \
        join.cpp  \
        privateMessage.cpp \
        Commands.cpp \
        modeCommand.cpp \
        invite.cpp \
        kick.cpp \
        motdCommand.cpp \
        noticeCommand.cpp \
        partCommand.cpp \
        topicCommand.cpp \
		Utils.cpp

OBJS_DIR = object_files
OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

GREEN        = \033[0;32m
RED          = \033[0;31m
YELLOW       = \033[0;33m
BLUE         = \033[0;34m
BOLD_GREEN   = \033[1;32m
BOLD_RED     = \033[1;31m
BOLD_YELLOW  = \033[1;33m
BOLD_BLUE    = \033[1;34m
RESET        = \033[0m

all: $(NAME)

$(OBJS_DIR)/%.o: SRC/%.cpp
	@echo "$(BOLD_YELLOW)compiling$(RESET) $(GREEN)$<$(RESET):\r\t\t\t\t\t"
	@mkdir -p $(OBJS_DIR)
	@$(CXX) $(CXXFLAGS) -c $(Includes) $< -o $@
	@echo "\r\t\t\t\t\t$(RED)$(CXX) $(CXXFLAGS)$(RESET)$(BLUE)-c $< -o $@$(RESET) $(BOLD_GREEN)<OK>$(RESET)"

$(NAME): $(OBJS) main.cpp
	@$(CXX) $(CXXFLAGS) $(Includes) $(OBJS) main.cpp -o $@
	@echo "$(BOLD_YELLOW)ircserv Compiled$(RESET): $(BOLD_GREEN)<OK>$(RESET)"

bonus: $(NAME_BONUS)

$(NAME_BONUS):
	@$(CXX) $(CXXFLAGS) bonus/ProfanityPatrol.cpp -o $@
	@echo "$(BOLD_YELLOW)ircserv_bonus Compiled$(RESET): $(BOLD_GREEN)<OK>$(RESET)"

clean:
	@if [ -e $(OBJS_DIR) ]; then \
		rm -rf $(OBJS_DIR); \
		echo "$(BOLD_YELLOW)ircserv Clean$(RESET): $(BOLD_GREEN)<OK>$(RESET)"; \
	fi

fclean: clean
	@if [ -e $(NAME) ]; then \
		rm -rf $(NAME); \
		echo "$(BOLD_YELLOW)ircserv Full-Clean$(RESET): $(BOLD_GREEN)<OK>$(RESET)"; \
	fi
	@if [ -e $(NAME_BONUS) ]; then \
		rm -rf $(NAME_BONUS); \
		echo "$(BOLD_YELLOW)ircserv_bonus Full-Clean$(RESET): $(BOLD_GREEN)<OK>$(RESET)"; \
	fi
	@if [ -e ircserv.DSYM ]; then \
		rm -rf ircserv.DSYM; \
	fi

re: fclean all

.PHONY: all clean fclean re bonus