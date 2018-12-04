PROFILE=DEBUG
CFLAGS-RELEASE=-O3
CFLAGS-DEBUG=
CFLAGS=${CFLAGS-${PROFILE}}

all: index myecho run
index: index.c
	gcc -o $(CFLAGS) index index.c
myecho: myecho.c
	gcc -o $(CFLAGS) myecho myecho.c
run:
	./index