files = src/main.c src/cpu.c src/mem.c

all: run

run: build
	./build/main

build: $(files)
	gcc $(files) -o build/main