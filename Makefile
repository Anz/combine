include Makefile.common

COMBINE_SRC = array.c map.c texture.c sprite.c camera.c scene.c render.c

COMBINE = ${COMBINE_SRC:%.c=bin/%.o}

all: bin bin/libcombine.a

bin:
	mkdir -p bin

bin/libcombine.a: ${COMBINE}
	ar -rcs bin/libcombine.a ${COMBINE}

bin/%.o: src/%.c
	${CC} ${CFLAGS} -o${<:src/%.c=bin/%.o} -c $<

install:
	cp bin/libcombine.a /usr/lib/
	mkdir -p /usr/include/combine
	cp -r include/* /usr/include/combine/

uninstall:
	rm /usr/lib/libcombine.a
	rm -r /usr/include/combine

clean:
	rm -rf bin
