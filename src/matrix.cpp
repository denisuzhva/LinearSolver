#include <iostream>
#include "../include/matrix.h"
#include "../include/cusmath.h"



/// Construct and Destruct
// Constructor
Matrix::Matrix(uint in_rows, uint in_cols, float **in_matrix) : 
	rows(in_rows), 
	cols(in_cols)
{
	allocMem();
	for (uint i = 0; i < rows; i++)
		for (uint j = 0; j < cols; j++)
			matrix[i][j] = in_matrix[i][j];
}


// Copy
Matrix::Matrix(uint in_rows, uint in_cols, const float& val) : 
	rows(in_rows), 
	cols(in_cols)
{
	allocMem();
	for (uint i = 0; i < rows; i++)
		for (uint j = 0; j < cols; j++)
			matrix[i][j] = val;
}


// Destructor with delete
Matrix::~Matrix() 
{
	deallocMem();
}


/// Access
// Get the number of rows
uint Matrix::getNumOfRows() const
{
	return this->rows;
}


// Get the number of columns
uint Matrix::getNumOfCols() const
{
	return this->cols;
}


// Print the matrix
void Matrix::printMatrix()
{
	for (uint i = 0; i < rows; i++)
	{
		for (uint j = 0; j < cols; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}


// Access an element by its indices 
float& Matrix::operator()(const uint& row, const uint& col)
{
	return this->matrix[row][col];
}


// Access an element by its indices (const)
const float& Matrix::operator()(const uint& row, const uint& col) const
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
	
	for (uint i = 0; i < rows; i++)
		for (uint j = 0; j < cols; j++)
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
		Matrix result(rows, cols, 0.0f);
		for (uint i = 0; i < rows; i++)
			for (uint j = 0; j < cols; j++)
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
		for (uint i = 0; i < rows; i++)
			for (uint j = 0; j < cols; j++)
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
		Matrix result(rows, cols, 0.0f);
		for (uint i = 0; i < rows; i++)
			for (uint j = 0; j < cols; j++)
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
		for (uint i = 0; i < rows; i++)
			for (uint j = 0; j < cols; j++)
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
		uint result_rows = rows;
		uint result_cols = mat_right.getNumOfCols();
		Matrix result(rows, cols, 0.0f);
		for (uint i = 0; i < result_rows; i++)
			for (uint j = 0; j < result_cols; j++)
				for (uint k = 0; k < cols; k++)
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
		Matrix result(rows, cols, 0.0f);
		for (uint i = 0; i < rows; i++)
			for (uint j = 0; j < rows; j++)
				for (uint k = 0; k < cols; k++)
					result.matrix[i][j] += this->matrix[i][k] * mat_right(k, j);
		return (*this = result);
	}
}


// Delete a row (starting with 0)
Matrix Matrix::deleteRow(uint row_del)
{
	if (row_del > rows)
	{
		std::cout << "[ERROR]: row number is higher than the maximum" << std::endl;
		return *this;
	}
	else
	{
		Matrix result(rows-1, cols, 0.0f);
		for (uint i = 0; i < row_del; i++)
			for (uint j = 0; j < cols; j++)
				result.matrix[i][j] = this->matrix[i][j];
		for (uint i = row_del; i < rows-1; i++)
			for (uint j = 0; j < cols; j++)
				result.matrix[i][j] = this->matrix[i+1][j];
		return result;
	}
}


// Delete a column (starting with 0)
Matrix Matrix::deleteCol(uint col_del)
{
	if (col_del > cols)
	{
		std::cout << "[ERROR]: column number is higher than the maximum" << std::endl;
		return *this;
	}
	else
	{
		Matrix result(rows, cols-1, 0.0f);
		for (uint i = 0; i < rows; i++)
			for (uint j = 0; j < col_del; j++)
				result.matrix[i][j] = this->matrix[i][j];
		for (uint i = 0; i < rows; i++)
			for (uint j = col_del; j < cols-1; j++)
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
		
	}
}


/// Misc
// Allocate memory for a matrix
void Matrix::allocMem()
{
	matrix = new float*[rows];
	for (uint i = 0; i < rows; i++)
		matrix[i] = new float[cols];
}


// Deallocate memory
void Matrix::deallocMem()
{
	for (uint i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}