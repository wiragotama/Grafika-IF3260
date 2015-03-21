#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <vector>

class Matrix {
	public:
	Matrix();
	Matrix(int n);
	Matrix(int row, int col);
	Matrix(const Matrix&);
	Matrix& operator= (const Matrix&);
	~Matrix();

	int getRow();

	void setDimension(int row, int col);

	double getElement(int row, int col);
	void setElement(int row, int col, double value);

	Matrix multiply(const Matrix&);

	static Matrix get3DRotationX(double radians);
	static Matrix get3DRotationY(double radians);

	static const int DIMENSION_SET = 1, NO_SUCH_ELEMENT = 2, CANT_MULTIPLY;

	private:
	void _setDimension(int row, int col);

	std::vector<double> elements;
	int row, col;
};

#endif
