INCLUDE_DIRS = -I include -I ext/*/include
FLAGS = -Wfatal-errors -Wall -std=c++14 -g

all: dir bin/simple_chess

dir:
	@mkdir -p bin

bin/%: src/%.cpp
	g++ $(FLAGS) -o $@ $< $(INCLUDE_DIRS)

