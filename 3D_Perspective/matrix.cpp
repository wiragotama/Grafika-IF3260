#include "matrix.h"

Matrix::Matrix() {
	row = col = 0;
}

Matrix::Matrix(int n) {
	_setDimension(n, n);
}

Matrix::Matrix(int row, int col) {
	_setDimension(row, col);
}

Matrix::Matrix(const Matrix& other) {
	row = other.row;
	col = other.col;
	elements = other.elements;
}

Matrix& Matrix::operator= (const Matrix& other) {
	if (this != &other) {
		row = other.row;
		col = other.col;
		elements = other.elements;
	}
	return *this;
}

Matrix::~Matrix() {}

int Matrix::getRow() {
	return row;
}

void Matrix::setDimension(int row, int col) {
	if (elements.size() == 0)
		_setDimension(row, col);

	else
		throw DIMENSION_SET;
}

void Matrix::_setDimension(int row, int col) {
	elements.resize(row*col, 0);
	this->row = row;
	this->col = col;
}

double Matrix::getElement(int row, int col) {
	int idx = row*this->col + col;

	if (idx >= 0 && idx < this->row*this->col)
		return elements[idx];
	else
		throw NO_SUCH_ELEMENT;
}

void Matrix::setElement(int row, int col, double value) {
	int idx = row*this->col + col;

	if (idx >= 0 && idx < this->row*this->col)
		elements[idx] = value;
	else
		throw NO_SUCH_ELEMENT;
}

Matrix Matrix::multiply(const Matrix& other) {
	if (col != other.row)
		throw CANT_MULTIPLY;

	else {
		Matrix result(row, other.col);

		for (int i = 0; i < row; i++)
			for (int k = 0; k < col; k++)
				for (int j = 0; j < other.col; j++)
					result.elements[i*col+j] += elements[i*col+k] *
						other.elements[k*other.col+j];

		return result;
	}
}

Matrix Matrix::get3DRotationX(double radians) {
	Matrix result(4);

	/* coordinate system [x y z 1] */
	/* 1 0    0   0
	 * 0 cos  sin 0
	 * 0 -sin cos 0
	 * 0 0    0   1 */
	result.setElement(0, 0, 1);
	result.setElement(3, 3, 1);
	double mcos = cos(radians), msin = sin(radians);
	result.setElement(1, 1, mcos);
	result.setElement(1, 2, msin);
	result.setElement(2, 1, -msin);
	result.setElement(2, 2, mcos);

	return result;
}

Matrix Matrix::get3DRotationY(double radians) {
	Matrix result(4);

	/* coordinate system [x y z 1] */
	/* cos 0  -sin 0
	 * 0   1  0    0
	 * sin 0  cos  0
	 * 0   0  0    1 */
	result.setElement(1, 1, 1);
	result.setElement(3, 3, 1);
	double mcos = cos(radians), msin = sin(radians);
	result.setElement(0, 0, mcos);
	result.setElement(2, 0, msin);
	result.setElement(0, 2, -msin);
	result.setElement(2, 2, mcos);

	return result;
}
