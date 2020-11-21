CC=clang++
ARGS=-std=c++17 -Wall
OUT=mancala

all:
	$(CC) $(ARGS) -o $(OUT) main.cpp

clean:
	rm $(OUT)
