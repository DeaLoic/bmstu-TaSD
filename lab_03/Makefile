all: app.exe test.exe

app.exe:
	gcc -Wall main.c array.c universal.c sparse_matrix.c -o app.exe

test.exe:
	gcc -Wall test.c array.c universal.c sparse_matrix.c -o test.exe

test:
	gcc -Wall test.c array.c universal.c sparse_matrix.c -o test -lm

main:
	gcc -Wall test.c array.c universal.c sparse_matrix.c -o test -lm