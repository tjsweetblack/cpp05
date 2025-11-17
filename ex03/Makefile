NAME		=	Bureaucrat

CXX			=	c++

CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98

#directories
SRC_DIR		=	srcs/
OBJ_DIR		=	obj/
INC_DIR		=	includes/

#source files
SRC_FILES	=	Bureaucrat.cpp \
				AForm.cpp \
				ShrubberyCreationForm.cpp \
				RobotomyRequestForm.cpp \
				PresidentialPardonForm.cpp \
				Intern.cpp \
				main.cpp

OBJ_FILES	=	$(SRC_FILES:.cpp=.o)

#paths
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

#all rule
all: $(NAME)
	

#compile the executable
$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "✓ Compiled $(NAME)"
	
#compile objects
$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) -o $@ -c $<
	@echo "✓ Compiled $<"


#clean rule
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	echo "✓ Cleaned object files"; \
	fi
	

#fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	echo "✓ Cleaned executable"; \
	fi
	@rm -f *_shrubbery
	@echo "✓ Cleaned shrubbery files"

#re rule
re: fclean all

.PHONY: all clean fclean re
