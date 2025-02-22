CC=gcc
CXX=g++
CFLAGS=-Os -ffunction-sections -Wl,--gc-sections,--strip-all -fno-asynchronous-unwind-tables -Wall -Wextra
CXXFLAGS=$(CFLAGS)

build: lite

updtss:
	rm -rf tinyss
	git clone https://github.com/etar125/tinyss.git
	rm -rf tinyss/.git
	rm -rf tinyss/.gitignore
	rm -rf tinyss/*.md
	rm -rf cctest.sh
	rm -rf docs
	mkdir -p tinyss/bin

library: tinyss/Makefile
	$(MAKE) -C tinyss lib CC="$(CC)" CFLAGS="$(CFLAGS)"

lite: library src/lite/lite.c tinyss/bin/tinyss.h tinyss/bin/libtinyss.a
	mkdir -p bin
	$(CC) src/lite/lite.c -o bin/lite125 -Ltinyss/bin -Itinyss/bin -ltinyss $(CFLAGS)

clean:
	rm -r bin/*

rebuild: clean build
