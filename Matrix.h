#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

#include "Coordinate.h"

template <class T> class Matrix {
public:
	Matrix(unsigned int, unsigned int, T);

	unsigned int get_width();
	unsigned int get_height();
	T get(Coordinate);
	T get(unsigned int, unsigned int);
	void set(Coordinate, T);
	void set(unsigned int, unsigned int, T);
	Coordinate pos(unsigned int x, unsigned int y);

private:
	unsigned int width;
	unsigned int height;
	std::vector<T> data;
};


// Template classes can only exist in header files, or every used instanciation
// of them must be declared in the .cpp file like:
// template class Matrix<int>;


template <class T>
Matrix<T>::Matrix(unsigned int width, unsigned int height, T default_value) : data(width * height, default_value) {
	this->width = width;
	this->height = height;
}

template <class T>
unsigned int Matrix<T>::get_width() {
	return this->width;
}

template <class T>
unsigned int Matrix<T>::get_height() {
	return this->height;
}

template <class T>
T Matrix<T>::get(Coordinate coord) {
	// TODO: Check that coordinate is for valid dimensions
	return this->data.at(coord.to_index());
}

template <class T>
T Matrix<T>::get(unsigned int x, unsigned int y) {
	return this->data.at(this->pos(x, y).to_index());
}

template <class T>
void Matrix<T>::set(unsigned int x, unsigned int y, T value) {
	this->data.at(this->pos(x, y).to_index()) = value;
}

template <class T>
void Matrix<T>::set(Coordinate coord, T value) {
	// TODO: Check that coordinate is for valid dimensions
	this->data.at(coord.to_index()) = value;
}

template <class T>
Coordinate Matrix<T>::pos(unsigned int x, unsigned int y) {
	return Coordinate(this->width, this->height, x, y);
}


#endif
