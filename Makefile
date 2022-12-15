.PHONY: directories clean

all: directories main

main: test/main.c
	@gcc $^ -Iinclude -Wall -Werror -o build/$@

directories: build

build:
	@mkdir -p $@

clean:
	@rm -rf build
