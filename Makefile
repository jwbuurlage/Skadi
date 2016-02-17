INCLUDE_DIR = include

all: dir bin/simple_chess

dir:
	@mkdir -p bin

bin/%: src/%.cpp
	g++ -std=c++14 -o $@ -g $< -I $(INCLUDE_DIR)

