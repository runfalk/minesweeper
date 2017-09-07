#ifndef BOARD_H
#define BOARD_H

#include "Matrix.h"

enum GameState {
	PLAYING,
	WIN,
	LOSE,
};


struct GameStatus {
	GameState state;
	unsigned int num_mines;
	unsigned int num_open_tiles;
	unsigned int num_tiles;
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
	Tile get(unsigned int, unsigned int);
	void render(bool);
private:
	Matrix<Tile> tiles;
	unsigned int num_mines = 0;
	unsigned int num_open_tiles = 0;
	GameState status = PLAYING;
};

#endif