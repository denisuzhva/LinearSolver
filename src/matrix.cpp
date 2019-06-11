#include <iostream>
#include "../include/matrix.h"



Matrix::Matrix(uint in_rows, uint in_cols, float **in_matrix) : 
	rows(in_rows), 
	cols(in_cols)
{
	matrix = new float*[rows];
	for(usint i = 0; i < rows; i++)
		matrix[i] = new float[cols];
	for(usint i = 0; i < rows; i++)
		for(usint j = 0; j < cols; j++)
			matrix[i][j] = in_matrix[i][j];
}


Matrix::Matrix(uint in_rows, uint in_cols, float& val) : 
	rows(in_rows), 
	cols(in_cols)
{
	matrix = new float*[rows];
	for(usint i = 0; i < rows; i++)
		matrix[i] = new float[cols];
	for(usint i = 0; i < rows; i++)
		for(usint j = 0; j < cols; j++)
			matrix[i][j] = val;
}


Matrix::~Matrix() 
{
	delete matrix;
}


uint Matrix::getNumOfRows() const
{
	return this->rows;
}


uint Matrix::getNumOfCols() const
{
	return this->cols;
}


void Matrix::printMatrix()
{
	for(usint i = 0; i < rows; i++)
	{
		for(usint j = 0; j < cols; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}


Matrix& Matrix::operator=(const Matrix &mat_source)
{
	if (&mat_source == this)
    	return *this;

	uint new_rows = mat_source.getNumOfRows();
	uint new_cols = mat_source.getNumOfCols();

	matrix = new float*[new_rows];
	for(usint i = 0; i < new_rows; i++)
		matrix[i] = new float[new_cols];
	
	for(usint i = 0; i < rows; i++)
		for(usint j = 0; j < cols; j++)
			matrix[i][j] = mat_source.matrix[i][j];
	
	rows = new_rows;
	cols = new_cols;

	return *this;
}