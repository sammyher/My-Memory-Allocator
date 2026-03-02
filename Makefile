# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinc

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
TEST_DIR = test

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_SRC = $(TEST_DIR)/test_main.c
TEST_OBJ = $(OBJ_DIR)/test_main.o

TARGET = mem_test

all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ): $(TEST_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

re: clean all

.PHONY: all clean re
