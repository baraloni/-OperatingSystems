CFLAGS = -Wextra -Wall -Wvla -g -I -pthread.
TARGET= libMapReduceFramework.a
CC = g++ -std=c++11
OBJ = MapReduceFramework.o Barrier.o

all: libMapReduceFramework.a

libMapReduceFramework.a: $(OBJ)
	ar rcs $(TARGET) $(OBJ)

%.o: %.cpp 
	$(CC) $(CFLAGS) $(NDB) -c $< -o $@

tar:
	tar cvf ex3.tar MapReduceFramework.cpp Barrier.cpp Barrier.h README

clean:
	rm -f *.o *.a *.tar *.out
