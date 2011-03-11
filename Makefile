include Makefile.common

COMBINE_SRC = array.c map.c texture.c texture_loader.c sprite.c scene.c level_loader.c render.c player.c main.c

COMBINE = ${COMBINE_SRC:%.c=bin/%.o}

all: bin bin/combine

bin:
	mkdir -p bin

bin/combine: ${COMBINE}
	${CC} ${CFLAGS} -obin/combine ${COMBINE} -lGLEW -lIL -lSDL

bin/%.o: src/%.c
	${CC} ${CFLAGS} -o${<:src/%.c=bin/%.o} -c $<

clean:
	rm -rf bin
