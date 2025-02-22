CC=gcc
CXX=g++
CFLAGS=-Os -ffunction-sections -Wl,--gc-sections,--strip-all -fno-asynchronous-unwind-tables -Wall -Wextra
CXXFLAGS=$(CFLAGS)

build: lite

updtss:
	cd src
	rm -rf tinyss
	git clone https://github.com/etar125/tinyss.git
	rm -rf tinyss/.git
	rm -rf tinyss/.gitignore
	rm -rf tinyss/*.md
	rm -rf cctest.sh
	rm -rf docs
	mkdir -p tinyss/bin

library: tinyss/makefile
	$(MAKE) -C tinyss lib CC="$(CC)" CFLAGS="$(CFLAGS)"

lite: library src/lite/lite.c src/tinyss/bin/tinyss.h src/tinyss/bin/libtinyss.a
	mkdir -p bin
	$(CC) src/lite/lite.c -o bin/lite125 -Lsrc/tinyss/bin -ltinyss $(CFLAGS)

clean:
	rm -r bin/*

rebuild: clean build
