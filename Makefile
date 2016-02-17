INCLUDE_DIRS = -I include -I ext/*/include

all: dir bin/simple_chess

dir:
	@mkdir -p bin

bin/%: src/%.cpp
	g++ -std=c++14 -o $@ -g $< $(INCLUDE_DIRS)

