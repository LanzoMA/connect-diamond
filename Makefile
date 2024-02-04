CC := gcc
srcFiles := src/main.c src/game.c
headers := include/game.h
buildDir := build/
exec := output
execPath := ${buildDir}${exec}

all: clean build run

clean:
	rm -rf ${buildDir}

build: ${srcFiles} ${headers}
	mkdir ${buildDir}
	${CC} -Wall -o ${execPath} -I include/ ${srcFiles}

run:
	./${execPath}
