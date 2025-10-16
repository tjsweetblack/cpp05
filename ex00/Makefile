# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badriano <badriano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 11:35:21 by badriano          #+#    #+#              #
#    Updated: 2025/10/16 11:35:23 by badriano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	Bureaucrat

CXX			=	c++

CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98

#directories
SRC_DIR		=	srcs/
OBJ_DIR		=	obj/
INC_DIR		=	includes/

#source files
SRC_FILES	=	Bureaucrat.cpp main.cpp

OBJ_FILES	=	$(SRC_FILES:.cpp=.o)

#paths
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

#all rule
all: $(NAME)
	

#compile the executable
$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	
#compile objects
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) -o $@ -c $<


#clean rule
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	fi
	

#fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	fi

#re rule
re: fclean all

#phony
.PHONY: all clean fclean re
