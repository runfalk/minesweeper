#include <iostream>
#include <set>
#include <deque>

#include "Coordinate.h"
#include "Matrix.h"


enum GameStatus {
	PLAYING,
	WIN,
	LOSE,
};

enum TileStatus {
	CLOSED,
	OPEN,
};


enum TileValue {
	BLANK,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	MINE,
};


struct Tile {
	TileStatus status;
	TileValue value;
};


class Board {
public:
	Board(unsigned int, unsigned int);
	bool add_mine(unsigned int, unsigned int);
	unsigned int get_width();
	unsigned int get_height();
	GameStatus get_status();
	Tile open(unsigned int, unsigned int);
	void render(bool);
private:
	Matrix<Tile> tiles;
	unsigned int num_mines = 0;
	unsigned int num_open_tiles = 0;
	GameStatus status = PLAYING;
};


Board::Board(unsigned int width, unsigned int height) :
	tiles(width, height, (Tile){CLOSED, BLANK}) {}


unsigned int Board::get_width() {
	return this->tiles.get_width();
}


unsigned int Board::get_height() {
	return this->tiles.get_height();
}

bool Board::add_mine(unsigned int x, unsigned int y) {
	Coordinate pos = this->tiles.pos(x, y);
	Tile tile = this->tiles.get(x, y);

	// Verify that we have not already placed a mine here
	if (tile.value == MINE) {
		return false;
	}

	// Make the given coordinate a mine
	tile.value = MINE;
	this->tiles.set(pos, tile);

	// Increment the adjacent mine count for all neighbors
	for (auto &coord : pos.get_neighbors()) {
		Tile current_neighbor = this->tiles.get(coord);
		current_neighbor.value = static_cast<TileValue>(
			static_cast<int>(current_neighbor.value) + 1);
		this->tiles.set(coord, current_neighbor);
	}

	this->num_mines++;

	return true;
}


Tile Board::open(unsigned int x, unsigned int y) {
	Coordinate pos = this->tiles.pos(x, y);
	Tile tile = this->tiles.get(x, y);

	// If the tile already was open we don't need to do any searching
	if (tile.status == OPEN) {
		return tile;
	}

	// If tile was blank we need to do a breadth first search
	std::set<Coordinate> handled;
	handled.insert(pos);

	std::deque<Coordinate> queue;
	queue.push_back(pos);

	while (queue.size()) {
		Coordinate coord = queue.front();
		queue.pop_front();

		// Mark the tile we are currently processing as open
		Tile current_tile = this->tiles.get(coord);
		current_tile.status = OPEN;
		this->tiles.set(coord, current_tile);
		this->num_open_tiles++;

		if (current_tile.value != BLANK) {
			continue;
		}

		for (auto &n : coord.get_neighbors()) {
			//Tile next_tile = this->tiles.get(n);
			//if (next_tile.value != MINE && !handled.count(n)) {
			if (!handled.count(n)) {
				handled.insert(n);
				queue.push_back(n);
			}
		}
	}

	// We must manually mark the tile as open since it was fetched before
	// opening
	tile.status = OPEN;


	unsigned int num_tiles = this->get_width() * this->get_height();
	if (tile.value == MINE) {
		this->status = LOSE;
	} else if (this->num_mines == num_tiles - this->num_open_tiles) {
		this->status = WIN;
	}

	return tile;
}

GameStatus Board::get_status() {
	return this->status;
}


void Board::render(bool reveal_all) {
	std::cout << "Board" << std::endl;
	std::cout << "-----" << std::endl;

	unsigned int width = this->get_width();
	unsigned int height = this->get_height();

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			Tile tile = this->tiles.get(col, row);

			if (reveal_all || tile.status == OPEN) {
				std::cout << " " << tile.value;
			} else {
				std::cout << " .";
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

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
