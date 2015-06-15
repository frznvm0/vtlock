# vtlock - virtual terminal locker
# See LICENSE file for copyright and license details.

include config.mk

SRC = vtlock.c
OBJ = ${SRC:.c=.o}

all: vtlock

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

vtlock: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f vtlock ${OBJ}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@install -o root -g root -m 4755 vtlock ${DESTDIR}${PREFIX}/bin/vtlock

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/vtlock

.PHONY: all clean install uninstall
