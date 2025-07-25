all: run

run: build
	./build/main

build: src/main.c
	gcc src/main.c -o build/main.exe