CFLAGS			= -O3 -s -DINI_MAX_LINE=2048

.SILENT: libinih.a clean
libinih.a: ini.o
	ar rcs $@ $^

ini.o: ini.c
	$(CC) -c $(CFLAGS) $^

.PHONY: clean
clean:
	rm -f *.a *.o

