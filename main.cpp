#include <iostream>

#include "Board.h"
#include "Coordinate.h"
#include "Matrix.h"


Coordinate read_coordinate(unsigned int width, unsigned int height) {
	unsigned int x;
	unsigned int y;

	std::cout << "Enter X and Y coordinate to open (zero-bound): ";
	while (!(std::cin >> x && std::cin >> y)) {
		std::cout << "Bad input, please enter X and Y coordinate: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return Coordinate(width, height, x, y);
}


int main()
{
	Board board(10, 10);
	board.add_mine(1, 1);
	board.add_mine(9, 9);

	GameStatus status;
	while ((status = board.get_status()) == PLAYING) {
		board.render(false);
		Coordinate coord = read_coordinate(board.get_width(), board.get_height());
		board.open(coord.get_x(), coord.get_y());		
	}

	board.render(true);

	switch (status) {
	case WIN:
		std::cout << "You win" << std::endl;
		break;
	case LOSE:
		std::cout << "You lose" << std::endl;
		break;
	case PLAYING:
		// Keep the compiler happy
		break;
	}

	return 0;
}
