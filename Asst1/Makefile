all: libBuild build

clean: 
	rm -f memgrind
libClean: mymalloc.c
	rm -f mymalloc.o
libBuild: mymalloc.c libClean
	gcc -c -g mymalloc.c -Wall
build: memgrind.c clean
	gcc memgrind.c mymalloc.o -g -o memgrind -Wall  
