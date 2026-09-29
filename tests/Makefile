CXX ?= g++
CXXFLAGS ?= -std=c++14 -g -Wall -Wextra
SOURCES := $(filter-out ../Watopoly/main.cc ../Watopoly/textdisplay.cc,$(wildcard ../Watopoly/*.cc))
HEADERS := $(wildcard ../Watopoly/*.h)

.PHONY: test clean
test: regressions
	python3 test_regressions.py

regressions: regressions.cc $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -I../Watopoly regressions.cc $(SOURCES) -o $@

clean:
	rm -f regressions
