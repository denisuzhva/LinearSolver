#include <iostream>
#include "../include/matrix.h"



/// Construct and Destruct
// Constructor
Matrix::Matrix(unsigned in_rows, unsigned in_cols, float **in_matrix) : 
	rows(in_rows), 
	cols(in_cols)
{
	/*
	allocMem();
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			matrix[i][j] = in_matrix[i][j];
	*/
	matrix = in_matrix;
}


// Copy
Matrix::Matrix(unsigned in_rows, unsigned in_cols, float val) : 
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
Matrix::Matrix(const Matrix &mat_right) :
	rows(mat_right.rows),
	cols(mat_right.cols)
{
	allocMem();
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			matrix[i][j] = mat_right.matrix[i][j];
}


// Destructor with delete
Matrix::~Matrix() 
{
	deallocMem();
}



/// Access
// Get the number of rows
const unsigned& Matrix::getNumOfRows() const
{
	return rows;
}


// Get the number of columns
const unsigned& Matrix::getNumOfCols() const
{
	return cols;
}


// Print the matrix
void Matrix::printMatrix() const
{
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < cols; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		if (i != rows-1)
			std::cout << "\n";
	}
	std::cout << std::endl;
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


// Set a row as the input row
void Matrix::setRow(unsigned row_set, const Matrix &in_row)
{
	if (in_row.rows != 1)
	{
		std::cout << "[ERROR]: not a row" << std::endl;
	}
	else if (in_row.cols != cols)
	{
		std::cout << "[ERROR]: the number of columns must match" << std::endl;
	}
	else
	{
		for (unsigned j = 0; j < cols; j++)
		{
			this->matrix[row_set][j] = in_row.matrix[0][j];
		}
	}
}


// Set a column as the input column
void Matrix::setCol(unsigned col_set, const Matrix &in_col)
{
	if (in_col.cols != 1)
	{
		std::cout << "[ERROR]: not a column" << std::endl;
	}
	else if (in_col.rows != rows)
	{
		std::cout << "[ERROR]: the number of rows must match" << std::endl;
	}
	else
	{
		for (unsigned i = 0; i < rows; i++)
		{
			this->matrix[i][col_set] = in_col.matrix[i][0];
		}
	}
}


// Delete a row (starting with 0)
Matrix Matrix::deleteRow(unsigned row_del) const
{
	if (rows == 1)
	{
		std::cout << "[ERROR]: a single row cannot be deleted" << std::endl;
		return *this;
	}
	else if (row_del >= rows)
	{
		std::cout << "[ERROR]: row number is higher than the maximum" << std::endl;
		return *this;
	}
	Matrix result(rows-1, cols);
	for (unsigned i = 0; i < row_del; i++)
		for (unsigned j = 0; j < cols; j++)
			result.matrix[i][j] = matrix[i][j];
	for (unsigned i = row_del; i < rows-1; i++)
		for (unsigned j = 0; j < cols; j++)
			result.matrix[i][j] = matrix[i+1][j];
	return result;
}


// Delete a column (starting with 0)
Matrix Matrix::deleteCol(unsigned col_del) const
{
	if (cols == 0)
	{
		std::cout << "[ERROR]: a single column cannot be deleted" << std::endl;
		return *this;
	}
	else if (col_del >= cols)
	{
		std::cout << "[ERROR]: column number is higher than the maximum" << std::endl;
		return *this;
	}
	Matrix result(rows, cols-1);
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < col_del; j++)
			result.matrix[i][j] = matrix[i][j];
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = col_del; j < cols-1; j++)
			result.matrix[i][j] = matrix[i][j+1];
	return result;
}


// Swap two rows
void Matrix::swapRows(unsigned row_1, unsigned row_2)
{
	Matrix temp = this->getRow(row_1);
	for (unsigned j = 0; j < cols; j++)
		matrix[row_1][j] = matrix[row_2][j];
	for (unsigned j = 0; j < cols; j++)
		matrix[row_2][j] = temp.matrix[0][j]; 
}


// Swap two columns
void Matrix::swapCols(unsigned col_1, unsigned col_2)
{
	Matrix temp = this->getCol(col_1);
	for (unsigned i = 0; i < cols; i++)
		matrix[i][col_1] = matrix[i][col_2];
	for (unsigned i = 0; i < cols; i++)
		matrix[i][col_2] = temp.matrix[i][0]; 
}


// Access a row by the [] operator
float* Matrix::operator[](unsigned row_num) const
{
	return matrix[row_num];
}



/// Arithmetic operations
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
			matrix[i][j] = mat_right.matrix[i][j];

	return *this;
}


// Add two matrices
Matrix Matrix::operator+(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when C := A + B" << std::endl;
		return *this;
	}
	else
	{
		Matrix result(rows, cols);
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
				result.matrix[i][j] = matrix[i][j] + mat_right.matrix[i][j];
		return result;
	}
}


// Add to a matrix
Matrix& Matrix::operator+=(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when A := A + B" << std::endl;
		return *this;
	}
	else
	{
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
				matrix[i][j] += mat_right.matrix[i][j];
		return *this;
	}
}


// Subtract two matrices
Matrix Matrix::operator-(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when C := A - B" << std::endl;
		return *this;
	}
	else
	{
		Matrix result(rows, cols);
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
				result.matrix[i][j] = matrix[i][j] - mat_right.matrix[i][j];
		return result;
	}
}


// Subtract from a matrix
Matrix& Matrix::operator-=(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when A := A - B" << std::endl;
		return *this;
	}
	else
	{
		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
				matrix[i][j] -= mat_right.matrix[i][j];
		return *this;
	}
}


// Multiply two matrices
Matrix Matrix::operator*(const Matrix &mat_right)
{
	if (cols != mat_right.getNumOfRows())
	{
		std::cout << "[ERROR]: the number of columns of A must match the number of rows of B when C := A * B" << std::endl;
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
					result.matrix[i][j] += matrix[i][k] * mat_right.matrix[k][j];
		return result;
	}
}


// Multiply self by another matrix
Matrix& Matrix::operator*=(const Matrix &mat_right)
{
	if (rows != mat_right.getNumOfRows() || cols != mat_right.getNumOfCols())
	{
		std::cout << "[ERROR]: the dimensions of A and B must match when A := A * B" << std::endl;
		return *this;
	}
	else
	{
		*this = (*this) * mat_right;
		return *this;
	}
}


// Multiply a matrix by a scalar
Matrix Matrix::operator*(float float_right)
{
	Matrix result(rows, cols);
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			result.matrix[i][j] = matrix[i][j] * float_right;
	return result;
}


// Multiply self by a scalar
Matrix& Matrix::operator*=(float float_right)
{
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			matrix[i][j] *= float_right;
	return *this;
}


// Divide a matrix by a scalar 
Matrix Matrix::operator/(float float_right)
{
	Matrix result(rows, cols);
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			result.matrix[i][j] = matrix[i][j] / float_right;
	return result;
}


// Divide self by a scalar
Matrix& Matrix::operator/=(float float_right)
{
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			matrix[i][j] /= float_right;
	return *this;
}



/// Matrix operations
// Transpose matrix
Matrix Matrix::transpose()
{
	Matrix result(cols, rows);
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			result.matrix[j][i] = matrix[i][j];
	return result;
}


// Make upper triangular using the gaussian elimination
void Matrix::makeGaussElimR()
{
	if (rows != 1)
	{
		unsigned pivot_num = 0;
		unsigned col_shift = 0;
		unsigned col_check = 0;
		while (col_check + col_shift < cols || pivot_num < rows)
		{
			bool allzeros = true;
			for (unsigned row_count = pivot_num; row_count < rows; row_count++)
			{
				if (matrix[row_count][col_check+col_shift] != 0)
				{
					allzeros = false;
					if (row_count != pivot_num)
					{
						swapRows(pivot_num, row_count);
					}
					for (unsigned sub_row_count = row_count+1; sub_row_count < rows; sub_row_count++)
					{
						Matrix newrow = getRow(sub_row_count) - getRow(row_count) * 
								matrix[sub_row_count][col_check+col_shift] *
								(1 / matrix[row_count][col_check+col_shift]);
						setRow(sub_row_count, newrow);	
					}
					col_check += col_shift + 1;
					col_shift = 0;
					break;
				}
			}
			if (allzeros == true)
			{
				col_shift++;
			}
			else
			{
				pivot_num++;
			}
		}
	}
}


// Make orthogonal
void Matrix::makeGramSchmidtQ()
{
	Matrix bckp = *this;
	bool uu_zero = false;
	for (unsigned k = 0; k < cols; k++)
	{
		Matrix u_k = this->getCol(k);
		for (unsigned j = 0; j < k; j++)
		{
			Matrix u_j = this->getCol(j);
			Matrix u_j_transp = u_j.transpose();
			Matrix a_k = this->getCol(k);
			float ua = (u_j_transp * a_k).matrix[0][0];
			float uu = (u_j_transp * u_j).matrix[0][0];
			if (uu == 0.0f)
			{
				uu_zero = true;
				break;
			}
			Matrix proj_jk = u_j * (ua / uu);  
			u_k -= proj_jk;
		}
		if (uu_zero == true)
		{
			*this = bckp;
			break;
		}

		this->setCol(k, u_k);
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
			det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
			return det; 
		}
		else
		{
			for (unsigned i = 0; i < cols; i++)
			{
				float multiplier = (*this)[0][i];
				Matrix minor = this->deleteRow(0);
				minor = minor.deleteCol(i);
				det += cusPower(-1.0f, i) * multiplier * minor.determinant();
			}
			return det;
		}
	}
}


// Sum of squared elements
float Matrix::sumOfSquares() const
{
	float result = 0;
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			result += matrix[i][j]*matrix[i][j];
	return result;
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



/// Non-member functions
// Multiply a matrix by a vector
Vector operator*(const Matrix &mat, const Vector &base_vect)
{
	const unsigned& mat_rows = mat.getNumOfRows();
	const unsigned& mat_cols = mat.getNumOfCols();
	const unsigned& base_len = base_vect.getLen();
	if (mat_cols != base_len)
	{
		std::cout << "[ERROR]: the number of matrix' columns must match the length of the vector when V2 := M * V1" << std::endl;
		return base_vect;
	}
	else
	{
		Vector result(mat_rows);
		for (unsigned i = 0; i < mat_rows; i++)
		{
			for (unsigned j = 0; j < mat_cols; j++)
			{
				result.setElement(i, (result[i] + mat[i][j] * base_vect[j]));
			}
		}
		return result;
	}

}


// Multiply a vector by a matrix
Vector operator*(const Vector &base_vect, const Matrix &mat)
{
	const unsigned& mat_rows = mat.getNumOfRows();
	const unsigned& mat_cols = mat.getNumOfCols();
	const unsigned& base_len = base_vect.getLen();
	if (mat_rows != base_len)
	{
		std::cout << "[ERROR]: the number of matrix' rows must match the length of the vector when V2 := V1 * M" << std::endl;
		return base_vect;
	}
	else
	{
		Vector result(mat_cols);
		for (unsigned i = 0; i < mat_cols; i++)
		{
			for (unsigned j = 0; j < mat_rows; j++)
			{
				result.setElement(i, (result[i] + mat[j][i] * base_vect[j]));
			}
		}
		return result;
	}
}
