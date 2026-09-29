CXX ?= g++
CXXFLAGS ?= -std=c++14 -g -Wall
CORE = $(filter-out ../Watopoly/main.cc ../Watopoly/textdisplay.cc,$(wildcard ../Watopoly/*.cc))
HEADERS = $(wildcard ../Watopoly/*.h)

.PHONY: test clean
regressions: regressions.cc $(CORE) $(HEADERS)
	$(CXX) $(CXXFLAGS) -I../Watopoly regressions.cc $(CORE) -o $@

test: regressions
	./regressions

clean:
	rm -f regressions
