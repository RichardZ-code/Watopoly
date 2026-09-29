CXX ?= g++
CXXFLAGS ?= -std=c++14 -g -Wall -Wextra
SOURCES = $(filter-out ../Watopoly/main.cc ../Watopoly/textdisplay.cc,$(wildcard ../Watopoly/*.cc))
HEADERS = $(wildcard ../Watopoly/*.h)

.PHONY: test clean
regression: regression.cc $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -I../Watopoly regression.cc $(SOURCES) -o $@

test: regression
	./regression

clean:
	rm -f regression .roundtrip.tmp
