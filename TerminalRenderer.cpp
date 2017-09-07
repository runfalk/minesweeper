#include <iostream>
#include <string>

#include "TerminalRenderer.h"

TerminalRenderer::TerminalRenderer(Board* board) {
	this->board = board;
}

void TerminalRenderer::render(bool reveal_all) {
	unsigned int width = this->board->get_width();
	unsigned int height = this->board->get_height();

	std::string top_left = "\u256d";
	std::string top_right = "\u256e";
	std::string bottom_left = "\u2570";
	std::string bottom_right = "\u256f";
	std::string horizontal = "\u2500";
	std::string vertical = "\u2502";
	std::string cross = "\u253c";

	// Print game information
	GameStatus status = this->board->get_status();
	std::cout << "Tiles left: " << (status.num_tiles - status.num_open_tiles) << std::endl;
	std::cout << "Mines: " << status.num_mines << std::endl;

	// Print top line
	std::cout << top_left;
	for (int i = 0; i < width - 1; i++) {
		std::cout << horizontal << "\u252c";
	}
	std::cout << horizontal << top_right << std::endl;

	// Print content
	for (int row = 0; row < height; row++) {
		// Print row separator, but skip on first row
		if (row) {
			std::cout << "\u251c" << horizontal;
			for (int i = 0; i < width - 1; i++) {
				std::cout << cross << horizontal;
			}
			std::cout << "\u2524" << std::endl;
		}

		for (int col = 0; col < width; col++) {
			Tile tile = this->board->get(col, row);
			if (reveal_all || tile.status == OPEN) {
				std::cout << vertical;
				switch (tile.value) {
					case MINE:
						std::cout << "*";
						break;
					case BLANK:
						std::cout << " ";
						break;
					default:
						std::cout << tile.value;
				}
			} else {
				std::cout << vertical << "\u2591";
			}
		}
		std::cout << vertical << std::endl;
	}

	// Print bottom line
	std::cout << bottom_left;
	for (int i = 0; i < width - 1; i++) {
		std::cout << horizontal << "\u2534";
	}
	std::cout << horizontal << bottom_right << std::endl;
}