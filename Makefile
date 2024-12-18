CC=gcc
CXX=g++
CFLAGS=-Os -ffunction-sections -Wl,--gc-sections,--strip-all -fno-asynchronous-unwind-tables -Wall -Wextra
CXXFLAGS=$(CFLAGS)
PREFIX=$(shell pwd)/bin

build: $(shell mkdir -p $(PREFIX))
	make -C src CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS)" CXXFLAGS="$(CXXFLAGS)" PREFIX=$(PREFIX)

clean:
	rm -r $(PREFIX)/*

rebuild: clean build
