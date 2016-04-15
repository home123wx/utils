OBJ = main.o TaskQueue.o
GCC = g++
Flags= -lpthread
all:main

main:${OBJ}
	${GCC} ${OBJ} ${Flags} -o $@
main.o:main.cpp
	${GCC} -c $< -o $@
TaskQueue.o:TaskQueue.cpp
	${GCC} -c $< -o $@

clean:
	rm -rf *.o
	rm -rf main
