CC=g++
CFLAGS=-ansi -Wall -g
OBJS=main.o city.o vector.o
simulator.out : $(OBJS)
	$(CC) -o simulator.out $(CFLAGS) $(OBJS)                 

main.o : main.cpp vector.h
	$(CC) -c $(CFLAGS) main.cpp

city.o : city.cpp city.h
	$(CC) -c $(CFLAGS) city.cpp

vector.o : vector.cpp vector.h city.h
	$(CC) -c $(CFLAGS) vector.cpp

test : 
	./simulator.out

clean : 
	rm -f $(OBJS) simulator.out
      
