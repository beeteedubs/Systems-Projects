all: libBuild build

clean: 
	rm -f assign1
libClean: library.c
	rm -f library.o
libBuild: library.c libClean
	gcc -c -g library.c -Wall
build: assign1.c clean
	gcc assign1.c library.o -g -o assign1 -Wall  
