all: app.out

app.o:
	gcc -Wall array.o info.o queue_array.o queue_list.o logic.o modeling.o request.o universal.o main.o -o app.exe

app.exe:
	gcc array.c info.c queue_array.c queue_list.c logic.c modeling.c request.c universal.c main.c -o app.exe

test.exe:
	gcc -Wall array.c info.c queue_array.c queue_list.c logic.c modeling.c request.c universal.c test.c -o test.exe

app.out:
	gcc -Wall array.c info.c queue_array.c queue_list.c logic.c modeling.c request.c universal.c main.c -o app.out -lm

test.out:
	gcc -Wall array.c info.c queue_array.c queue_list.c logic.c modeling.c request.c universal.c test.c -o test.out -lm
