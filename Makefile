.SILENT: all clean
.PHONY: d_dist libs dude clean
all: lib dude |d_dist
	mv src/dude dist/dude

d_dist:
	mkdir -p dist

d_lib:
	mkdir -p lib
	mkdir -p include/dui
	mkdir -p include/inih

lib: |d_lib
	make -C src/dui/
	mv src/dui/libdui.a lib/
	cp src/dui/dui.h include/dui/dui.h
	make -C src/inih/
	mv src/inih/libinih.a lib/
	cp src/inih/ini.h include/inih/ini.h

dude:
	make -C src/

clean:
	make -C src/dui/ clean
	make -C src/inih/ clean
	make -C src/ clean
	rm -rf dist lib include
