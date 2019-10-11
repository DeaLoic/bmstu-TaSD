all: app.exe test.exe

app.exe:
	gcc -Wall main.c array.c matrix.c universal.c sparse_matrix.c logic.c -o app.exe

test.exe:
	gcc -Wall test.c array.c matrix.c universal.c sparse_matrix.c logic.c -o test.exe

main.out:
	gcc -Wall test.c array.c matrix.c universal.c sparse_matrix.c logic.c -o main.out -lm

test.out:
	gcc -Wall test.c array.c matrix.c universal.c sparse_matrix.c logic.c -o test.out -lm
