D_LIB		= ../lib
D_INCLUDE	= ../include 

CDEFINES	= -D_LARGEFILE64_SOURCE -DDEBUG
CWARNINGS	= -Wall -Wno-multichar -Wno-switch -Wno-unused-label
CFLAGS		= -std=c99 $(CDEFINES) $(CWARNINGS) -I$(D_INCLUDE) -L$(D_LIB) -g
#LIBS		= $(D_LIB)/libdui.a $(D_LIB)/libinih.a -lapr-1 -lSDL2
LIBS		= -lapr-1 -lSDL2

.SILENT: dude clean
.PHONY: clean

SRC = \
      dude.c log.c util.c options.c

OBJS = $(SRC:.c=.o)

dude: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

dude.o: dude.c
	$(CC) -c $(CFLAGS) $<

log.o: log.c
	$(CC) -c $(CFLAGS) $<

util.o: util.c
	$(CC) -c $(CFLAGS) $<

options.o: options.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f *.o dude dude.exe

