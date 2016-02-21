INCLUDE_DIRS = -I../include -I../ext/catch/include  -I../ext/jwutil/include

FLAGS = -Wall -std=c++14 -g
OBJS = bin/catch.o bin/notation.o bin/game_rules.o

all: dir $(OBJS) bin/tests

dir:
	@mkdir -p bin

bin/%.o: %.cpp
	g++ $(FLAGS) $(INCLUDE_DIRS) -o $@ -c $<

bin/tests: $(OBJS)
	g++ -o $@ $(OBJS)
