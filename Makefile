CPP := $(shell find . -name '*.cpp')
HEADERS := $(shell find . -name '*.h')

minesweeper: $(CPP) $(HEADERS)
	g++ -o minesweeper -std=c++11 $(CPP)
