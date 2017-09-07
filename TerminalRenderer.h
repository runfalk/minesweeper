#ifndef TERMINAL_RENDERER_H
#define TERMINAL_RENDERER_H

#include "Board.h"

class TerminalRenderer {
public:
	TerminalRenderer(Board*);
	void render(bool);
private:
	Board* board;
};

#endif