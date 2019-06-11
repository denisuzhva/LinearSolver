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
		for(usint j; j < cols; j++)
			matrix[i][j] = in_matrix[i][j];
}

Matrix::~Matrix() 
{
}

uint Matrix::getNumOfRows()
{
	return rows;
}

uint Matrix::getNumOfCols()
{
	return cols;
}

void Matrix::printMatrix()
{
	for(usint i = 0; i < rows; i++)
	{
		for(usint j; j < cols; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
}
