CC = g++
CFLAGS = -Wall
PROG1 = framebuffer
PROG2 = ex1
PROG3 = ex2

SRCS1 = main.cpp
SRCS2 = ex1.cpp
SRCS3 = ex2.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lGLEW -lglfw -lGL -std=c++0x -lSOIL -lassimp
endif

all: $(PROG1) $(PROG2) $(PROG3)

$(PROG1):	$(SRCS1)
	$(CC) $(CFLAGS) -o $(PROG1) $(SRCS1) $(LIBS)

$(PROG2):	$(SRCS2)
	$(CC) $(CFLAGS) -o $(PROG2) $(SRCS2) $(LIBS)

$(PROG3):	$(SRCS3)
	$(CC) $(CFLAGS) -o $(PROG3) $(SRCS3) $(LIBS)

clean:
	rm -f $(PROG)
