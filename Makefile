build:
	gcc -Wall -std=c99 ./src/test01.c -lSDL2 -o Learninc_C

window:
	gcc -Wall -std=c99 ./src/window.c -lSDL2 -o Window

gameengine:
	gcc -Wall -std=c99 ./src/gameengine.c -lSDL2 -o GameEngine


run:
	./Learninc_C

run-window:
	./Window

run-gameengine:
	./GameEngine

clean:
	rm Learninc_C Window GameEngine

clean-window:

	rm Window
clean-gameengine:
	rm GameEngine