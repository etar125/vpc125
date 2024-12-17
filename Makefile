CC=tcc
PREFIX=$(shell pwd)/bin

all: $(shell mkdir -p $(PREFIX))
	make -C src CC=$(CC) PREFIX=$(PREFIX)
