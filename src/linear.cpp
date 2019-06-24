#include <iostream>
#include "../include/linear.h"



// Multiply a matrix by a vector
Vector operator*(const Matrix& mat, const Vector& base_vect)
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
				result.setElement(i, (result(i) + mat(i, j) * base_vect(j)));
			}
		}
		return result;
	}

}


// Multiply a vector by a matrix
Vector operator*(const Vector& base_vect, const Matrix& mat)
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
				result.setElement(i, (result(i) + mat(j, i) * base_vect(j)));
			}
		}
		return result;
	}
}


// Find x in Ax = b given A and b
Vector solveLinEq(Matrix matrix_A, Vector vector_b)
{
	const unsigned a_rows = matrix_A.getNumOfRows();
	const unsigned a_cols = matrix_A.getNumOfCols();
	const unsigned b_len = vector_b.getLen();
	if (a_rows != b_len)
	{
		std::cout << "[ERROR]: the number of rows in A must match the length of b in Ax = b" << std::endl;
		return vector_b;	
	}
	else
	{
		if (a_rows != 1)
		{
			unsigned pivot_num = 0;
			unsigned col_shift = 0;
			while (pivot_num + col_shift < a_cols || pivot_num < a_rows)
			{
				bool allzeros = true;
				for (unsigned row_count = pivot_num; row_count < a_rows; row_count++)
				{
					if (matrix_A(row_count, pivot_num+col_shift) != 0)
					{
						allzeros = false;
						if (row_count != pivot_num)
						{
							matrix_A.swapRows(pivot_num, row_count);
							vector_b.swapElements(pivot_num, row_count);
						}
						for (unsigned sub_row_count = row_count+1; sub_row_count < a_rows; sub_row_count++)
						{
							Matrix newrow = matrix_A.getRow(sub_row_count) - 
									matrix_A.getRow(row_count) * 
									matrix_A(sub_row_count, pivot_num+col_shift) *
									(1 / matrix_A(row_count, pivot_num+col_shift));
							float newelement = vector_b.getElement(sub_row_count) - 
									   vector_b.getElement(row_count) *
									   matrix_A(sub_row_count, pivot_num+col_shift) *
									   (1 / matrix_A(row_count, pivot_num+col_shift));
							matrix_A.setRow(sub_row_count, newrow);	
							vector_b.setElement(sub_row_count, newelement);
						}
						col_shift = 0;
						break;
					}
				}
				if (allzeros == true)
					col_shift++;
				else
					pivot_num++;
			}
		}
		matrix_A.printMatrix();
		vector_b.printVector();
		const unsigned num_of_vars = a_cols;
		float row_sum = 0;
		Vector result(num_of_vars);
		bool row_check[num_of_vars];
		
		for (unsigned i = 0; i < num_of_vars; i++)
		{
			row_check[i] = false;
		}
		
		for (unsigned i = a_rows-1; i >= 0; i--)
		{
			float b_i = vector_b(i);
			for (unsigned j = 0; j < a_cols; j++)
			{
				b_i -= result(j) * matrix_A(i, j);
				row_sum += matrix_A(i, j);
			}	
			for (unsigned j = 0; j < a_cols; j++)
			{
				if (!row_check[j] && matrix_A(i, j) != 0)
				{
					row_check[j] = true;
					result.setElement(j, b_i / row_sum);
				}
			}
			row_sum = 0;
		}
		return result;
	}
}
