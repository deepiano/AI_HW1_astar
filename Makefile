OBJS = AStar.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

ai1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ai1

main.o : main.cpp Astar.h
	$(CC) $(CFLAGS) main.cpp

Astar.o : AStar.h Astar.cpp
	$(CC) $(CFLAGS) Astar.cpp

clean:
	\rm *.o ai1