main: main.o sum.o
	gcc main.o sum.o -o main
main.o: main.c
	gcc -c main.c -o main.o
sum.o: sum.c
	gcc -c sum.c -o sum.o
.PHONY: clean clean_main rebuild
clean:
	rm -f sum.o main.o  main
clean_main:
	rm -f main
rebuild: clean main
