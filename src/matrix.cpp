#include <iostream>
#include "../include/matrix.h"
#include "../include/cusmath.h"



/// Construct and Destruct
// Constructor
Matrix::Matrix(unsigned in_rows, unsigned in_cols, float **in_matrix) : 
	rows(in_rows), 
	cols(in_cols)
{
	allocMem();
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			matrix[i][j] = in_matrix[i][j];
}


// Copy
Matrix::Matrix(unsigned in_rows, unsigned in_cols, const float& val) : 
	rows(in_rows), 
	cols(in_cols)
{
	allocMem();
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			matrix[i][j] = val;
}


// Copy 2
Matrix::Matrix(unsigned in_rows, unsigned in_cols) :
	rows(in_rows),
	cols(in_cols)
{
	allocMem();
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			matrix[i][j] = 0.0f;
}


// Conversion
Matrix::Matrix(const Matrix& mat_right) :
	rows(mat_right.rows),
	cols(mat_right.cols)
{
	allocMem();
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			matrix[i][j] = mat_right(i, j);
}


// Destructor with delete
Matrix::~Matrix() 
{
	deallocMem();
}


/// Access
// Get the number of rows
unsigned Matrix::getNumOfRows() const
{
	return this->rows;
}


// Get the number of columns
unsigned Matrix::getNumOfCols() const
{
	return this->cols;
}


// Print the matrix
void Matrix::printMatrix() const
{
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < cols; j++)
		{
			std::cout << this->matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}


// Access an element by its indices (const)
const float& Matrix::operator()(const unsigned& row, const unsigned& col) const
{
	return this->matrix[row][col];
}


/// Operations
// Matrix assignment
Matrix& Matrix::operator=(const Matrix &mat_right)
{
	if (&mat_right == this)
    	return *this;

	deallocMem();
	rows = mat_right.getNumOfRows();
	cols = mat_right.getNumOfCols();
	allocMem();
	
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			this->matrix[i][j] = mat_right(i, j); 

	return *this;
}


// Add two matrices
Matrix Matrix::operator+(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when C = A + B" << std::endl;
		return *this;
	}
	else
	{
		Matrix result(rows, cols);
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
				result.matrix[i][j] = this->matrix[i][j] + mat_right(i, j);
		return result;
	}
}


// Add to a matrix
Matrix& Matrix::operator+=(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when A -> A + B" << std::endl;
		return *this;
	}
	else
	{
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
				this->matrix[i][j] += mat_right(i, j);
		return *this;
	}
}


// Subtract two matrices
Matrix Matrix::operator-(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when C = A - B" << std::endl;
		return *this;
	}
	else
	{
		Matrix result(rows, cols);
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
				result.matrix[i][j] = this->matrix[i][j] - mat_right(i, j);
		return result;
	}
}


// Subtract from a matrix
Matrix& Matrix::operator-=(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when A -> A - B" << std::endl;
		return *this;
	}
	else
	{
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
				this->matrix[i][j] -= mat_right(i, j);
		return *this;
	}
}


// Multiply two matrices
Matrix Matrix::operator*(const Matrix &mat_right)
{
	if (cols != mat_right.getNumOfRows())
	{
		std::cout << "[ERROR]: the number of columns of A must match the number of rows of B when C = A * B" << std::endl;
		return *this;
	} 
	else
	{		
		unsigned result_rows = rows;
		unsigned result_cols = mat_right.getNumOfCols();
		Matrix result(rows, cols);
		for (unsigned i = 0; i < result_rows; i++)
			for (unsigned j = 0; j < result_cols; j++)
				for (unsigned k = 0; k < cols; k++)
					result.matrix[i][j] += this->matrix[i][k] * mat_right(k, j);
		return result;
	}
}


// Multiply self by another matrix
Matrix& Matrix::operator*=(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when A -> A * B" << std::endl;
		return *this;
	}
	else
	{
		Matrix result(rows, cols);
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < rows; j++)
				for (unsigned k = 0; k < cols; k++)
					result.matrix[i][j] += this->matrix[i][k] * mat_right(k, j);
		return (*this = result);
	}
}


// Get a row of number row_get
Matrix Matrix::getRow(unsigned row_get) const
{
	Matrix mat_row(1, cols);
	for (unsigned j = 0; j < cols; j++)
		mat_row.matrix[0][j] = this->matrix[row_get][j];
	return mat_row;
}


// Get a column of number col_get
Matrix Matrix::getCol(unsigned col_get) const
{
	Matrix mat_col(rows, 1);
	for (unsigned i = 0; i < cols; i++)
		mat_col.matrix[i][0] = this->matrix[i][col_get];
	return mat_col;
}


// Delete a row (starting with 0)
Matrix Matrix::deleteRow(unsigned row_del) const
{
	if (row_del >= rows)
	{
		std::cout << "[ERROR]: row number is higher than the maximum" << std::endl;
		return *this;
	}
	else
	{
		Matrix result(rows-1, cols);
		for (unsigned i = 0; i < row_del; i++)
			for (unsigned j = 0; j < cols; j++)
				result.matrix[i][j] = this->matrix[i][j];
		for (unsigned i = row_del; i < rows-1; i++)
			for (unsigned j = 0; j < cols; j++)
				result.matrix[i][j] = this->matrix[i+1][j];
		return result;
	}
}


// Delete a column (starting with 0)
Matrix Matrix::deleteCol(unsigned col_del) const
{
	if (col_del >= cols)
	{
		std::cout << "[ERROR]: column number is higher than the maximum" << std::endl;
		return *this;
	}
	else
	{
		Matrix result(rows, cols-1);
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < col_del; j++)
				result.matrix[i][j] = this->matrix[i][j];
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = col_del; j < cols-1; j++)
				result.matrix[i][j] = this->matrix[i][j+1];
		return result;
	}
}


// Find determinant
float Matrix::determinant() const
{
	if (rows != cols)
	{
		std::cout << "[ERROR]: only square matrices may have a determinant" << std::endl;
		return 0.0f;
	}
	else
	{
		float det = 0.0f;	
		if (rows == 2)
		{
			det = this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
			return det; 
		}
		else
		{
			for (unsigned i = 0; i < cols; i++)
			{
				float multiplier = (*this)(0, i);
				Matrix minor = this->deleteRow(0);
				minor = minor.deleteCol(i);
				det += cuspower(-1.0f, i) * multiplier * minor.determinant();
			}
			return det;
		}
	}
}


/// Misc
// Allocate memory for a matrix
void Matrix::allocMem()
{
	matrix = new float*[rows];
	for (unsigned i = 0; i < rows; i++)
		matrix[i] = new float[cols];
}


// Deallocate memory
void Matrix::deallocMem()
{
	for (unsigned i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}
