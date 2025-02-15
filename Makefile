CC = gcc
CFLAGS = -g -O0 -std=gnu17 -Wall
SOURCES = $(wildcard src/*.c)
TARGET = program

# Diretórios
SRC_DIR = src
INC_DIR = include

# Linking dos objetos
all: 
	$(CC) $(CFLAGS) $(OBJ) $(SOURCES) -o exec

zip: 
	@rm -f *.zip
	zip -r rec.zip $(INC_DIR)/* $(SRC_DIR)/* ./Makefile

run:
	./exec