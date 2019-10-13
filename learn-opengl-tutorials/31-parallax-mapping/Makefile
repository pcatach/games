CC = g++
CFLAGS = -Wall
PROG1 = normal

SRCS1 = main.cpp

LIBS = -lGLEW -lglfw -lGL -std=c++0x -lSOIL -lassimp

all: $(PROG1)

$(PROG1):	$(SRCS1)
	$(CC) $(CFLAGS) -o $(PROG1) $(SRCS1) $(LIBS)


clean:
	rm -f $(PROG)
