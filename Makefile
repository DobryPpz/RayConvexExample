all:
	gcc `find . -type f -iname "*.c"` -Wall -I src -lm -o hull `pkg-config --cflags --libs raylib`