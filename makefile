CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: simplegraph

simplegraph: simplegraph.cc graph.cc graph.h 
	g++ $(CXXFLAGS) -o simplegraph simplegraph.cc graph.cc

clean:
	rm -f simplegraph

.PHONY: all clean
