CC = g++

# Build program
all: main.cpp parsers.cpp strsepcompatible.c 
	@$(CC) -o baseball_stats.o main.cpp parsers.cpp strsepcompatible.c

# Clean build
clean:
	@rm baseball_stats.o
