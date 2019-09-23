all: app.exe

app.exe:
	gcc -Wall -Werror -pedantic main.c longNumber.c longAriph.c universal.c -o app.exe

test.exe:
	gcc -Wall -Werror -pedantic test.c array_handler.c calculate_logic.c -o test.exe

clean:
	rm *.exe

cleanLinux:
	rm main test

app:
	gcc -Wall main.c array_handler.c calculate_logic.c -o app -lm

test:
	gcc -Wall test.c array_handler.c calculate_logic.c -o test -lm