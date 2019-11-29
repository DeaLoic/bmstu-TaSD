all: test.out

test.out: test.o bin_tree.o bst.o
	gcc -Wall test.o bin_tree.o bst.o -o test.out

test.o:
	gcc -Wall test.c -c test.o

bin_tree.o:
	gcc -Wall bin_tree.c -c bin_tree.o

bst.o:
	gcc -Wall bst.c -c bst.o
