NAME := RPN
TEST_NAME := tests

CXX := c++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -MMD -g3

OBJ := RPN.o

MAIN_OBJ := main.o

TEST_OBJ := test.o

INCLUDES := -I.

DEPS := ${OBJ:.o=.d} ${MAIN_OBJ:.o=.d} ${TEST_OBJ:.o=.d}

RM := rm -f

#############################################################################

$(NAME): $(OBJ) $(MAIN_OBJ)
	$(CXX) $(OBJ) $(MAIN_OBJ) -o $(NAME)

$(TEST_NAME): $(OBJ) $(TEST_OBJ)
	$(CXX) $(OBJ) $(TEST_OBJ) -o $(TEST_NAME)

test: $(TEST_NAME)
	./$(TEST_NAME)

all: $(NAME)

clean:
	$(RM) $(DEPS)
	$(RM) $(OBJ)
	$(RM) $(MAIN_OBJ)
	$(RM) $(TEST_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test

-include $(DEPS)