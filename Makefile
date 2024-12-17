CC=tcc
PREFIX=$(shell pwd)/bin

build: $(shell mkdir -p $(PREFIX))
	make -C src CC=$(CC) PREFIX=$(PREFIX)

clean:
	rm -r $(PREFIX)/*

rebuild: clean build
