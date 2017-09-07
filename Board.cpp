#include <iostream>
#include <set>
#include <deque>

#include "Board.h"

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

Tile Board::get(unsigned int x, unsigned int y) {
	return this->tiles.get(x, y);
}

GameStatus Board::get_status() {
	return {
		this->status,
		this->num_mines,
		this->num_open_tiles,
		this->get_width() * this->get_height(),
	};
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