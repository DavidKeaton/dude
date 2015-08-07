D_LIB		= ../../lib
D_INCLUDE	= ../../include 

CWARNINGS	= -Wall -Wno-multichar
CFLAGS		= -std=c99 $(CWARNINGS) -I$(D_INCLUDE) -L$(D_LIB) -g
LIBS		= -lapr-1

.SILENT: libdui.a clean

SRC = \
	  dui.c mouse.c keyboard.c menus.c dialog.c edit.c text.c graphics.c

OBJS = $(SRC:.c=.o)

libdui.a: $(OBJS)
	ar rcs $@ $^

dui.o: dui.c
	$(CC) -c $(CFLAGS) $<

mouse.o: mouse.c
	$(CC) -c $(CFLAGS) $<

keyboard.o: keyboard.c
	$(CC) -c $(CFLAGS) $<

menus.o: menus.c
	$(CC) -c $(CFLAGS) $<

dialog.o: dialog.c
	$(CC) -c $(CFLAGS) $<

edit.o: edit.c
	$(CC) -c $(CFLAGS) $<

text.o: text.c
	$(CC) -c $(CFLAGS) $<

graphics.o: graphics.c
	$(CC) -c $(CFLAGS) $<


.PHONY: clean
clean:
	rm -f *.a
	rm -f *.o

