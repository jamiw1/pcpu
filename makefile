all: run

run: build
	./build/main

build: src/main.c
	mkdir build
	gcc src/main.c -o build/main.exe