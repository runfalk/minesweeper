#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <vector>

class Coordinate {
public:
	Coordinate(unsigned int, unsigned int, unsigned int, unsigned int);

	unsigned int get_width();
	unsigned int get_height();
	unsigned int get_x();
	unsigned int get_y();
	unsigned int to_index();
	Coordinate left();
	Coordinate right();
	Coordinate up();
	Coordinate down();
	std::vector<Coordinate> get_neighbors();

	// Implement less than for 
	bool operator<(Coordinate const &) const;

	// Support printing of coordinates
	friend std::ostream &operator<<(std::ostream &, Coordinate const &);

private:
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
};

std::ostream &operator<<(std::ostream &, Coordinate const &);
#endif
