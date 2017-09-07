#include <iostream>
#include <stdexcept>

#include "Coordinate.h"


Coordinate::Coordinate(unsigned int width, unsigned int height, unsigned int x, unsigned int y) {
	this->width = width;
	this->height = height;

	if (x >= width) {
		throw std::out_of_range("x coordinate is out of range");
	} else if (y >= height) {
		throw std::out_of_range("y coordinate is out of range");
	}

	this->x = x;
	this->y = y;
}


unsigned int Coordinate::get_width() {
	return this->width;
}


unsigned int Coordinate::get_height() {
	return this->height;
}


unsigned int Coordinate::get_x() {
	return this->x;
}


unsigned int Coordinate::get_y() {
	return this->y;
}


unsigned int Coordinate::to_index() {
	return this->width * this->y + this->x;
}


Coordinate Coordinate::left() {
	return Coordinate(this->width, this->height, this->x - 1, this->y);
}


Coordinate Coordinate::right() {
	return Coordinate(this->width, this->height, this->x + 1, this->y);
}


Coordinate Coordinate::up() {
	return Coordinate(this->width, this->height, this->x, this->y - 1);
}


Coordinate Coordinate::down() {
	return Coordinate(this->width, this->height, this->x, this->y + 1);
}


std::vector<Coordinate> Coordinate::get_neighbors() {
	std::vector<Coordinate> neighbors;
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if (dx == 0 && dy == 0) {
				continue;
			}

			try {
				Coordinate coord(this->width, this->height, this->x + dx, this->y + dy);
				neighbors.push_back(coord);
			} catch (const std::out_of_range &e) {}
		}
	}

	return neighbors;
}


bool Coordinate::operator<(Coordinate const &other) const {
	return this->x < other.x || (this->x == other.x && this->y < other.y);
}

std::ostream &operator<<(std::ostream &os, Coordinate const &coord) { 
    return os << "<Coordinate x=" << coord.x << " y=" << coord.y << ">";
}
