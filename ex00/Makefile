MAIN_NAME := btc
TEST_NAME := tests/tests

CXX := c++

CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -MMD -g3

OBJ :=	BitcoinExchange.o \
	Date.o \

MAIN_OBJ := main.o

TEST_OBJ := test.o

INCLUDES := -I.

DEPS := ${OBJ:.o=.d} ${MAIN_OBJ:.o=.d} ${TEST_OBJ:.o=.d}

RM := rm -f

#############################################################################

$(MAIN_NAME): $(OBJ) $(MAIN_OBJ)
	$(CXX) $(OBJ) $(MAIN_OBJ) -o $(MAIN_NAME)

$(TEST_NAME): $(OBJ) $(TEST_OBJ)
	$(CXX) $(OBJ) $(TEST_OBJ) -o $(TEST_NAME)

test: $(TEST_NAME)
	bash tests/data_fails_create.sh
	./$(TEST_NAME)

all: $(MAIN_NAME)

clean:
	$(RM) $(DEPS)
	$(RM) $(OBJ)
	$(RM) $(MAIN_OBJ)
	$(RM) $(TEST_OBJ)

fclean: clean
	$(RM) $(MAIN_NAME)
	$(RM) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test

-include $(DEPS)