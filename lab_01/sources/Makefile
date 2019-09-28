all: app.exe

app.exe:
	gcc -Wall -Werror -pedantic main.c longNumber.c longAriph.c universal.c -o app.exe

clean:
	rm *.exe

cleanLinux:
	rm main test

app:
	gcc -Wall main.c longNumber.c longAriph.c universal.c -o app -lm
