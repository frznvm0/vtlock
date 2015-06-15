# paths
PREFIX = /usr/local

# includes and libs
INCS = -I. -I/usr/include
LIBS = -L/usr/lib

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\"
CFLAGS = -std=c99 -pedantic -Wall -Os ${INCS} ${CPPFLAGS}
LDFLAGS = -s ${LIBS}

# compiler and linker
CC = cc
