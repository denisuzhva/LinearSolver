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
	unsigned column_permute[a_cols];
	for (unsigned i = 0; i < a_cols; i++)
	{
		column_permute[i] = i;
	}
	if (a_rows != b_len)
	{
		std::cout << "[ERROR]: the number of rows in A must match the length of b in Ax = b" << std::endl;
		return vector_b;	
	}
	unsigned pivot_num = 0;
	if (a_rows != 1)
	{
		unsigned col_shift = 0;
		while ((pivot_num + col_shift < a_cols) && (pivot_num < a_rows))
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
					if (col_shift != 0)
					{
						matrix_A.swapCols(pivot_num, pivot_num+col_shift);
						column_permute[pivot_num] = pivot_num+col_shift;
						column_permute[pivot_num+col_shift] = pivot_num;
					}
					col_shift = 0;
					break;
				}
			}
			if (allzeros == true)
			{
				if (pivot_num == a_cols-1 && vector_b(pivot_num) != 0)
				{
					std::cout << "[ERROR]: the system is unsolvable" << std::endl;
					return vector_b;
				}
				col_shift++;
			}	
			else
			{
				pivot_num++;
			}
		}
	}
	pivot_num--;
	for (unsigned row_count = pivot_num; row_count >= 0 && row_count != 4294967295; row_count--)
	{
		Matrix current_row = matrix_A.getRow(row_count);
		float denominator = current_row(0, row_count);
		current_row /= denominator;
		vector_b.setElement(row_count, vector_b(row_count) / denominator);
		matrix_A.setRow(row_count, current_row);
		for (unsigned sub_row_count = row_count-1; sub_row_count >= 0 && sub_row_count != 4294967295; sub_row_count--)
		{
			Matrix current_sub_row = matrix_A.getRow(sub_row_count);
			float multiplier = current_sub_row(0, row_count);
			current_sub_row -= current_row * multiplier;
			vector_b.setElement(sub_row_count, vector_b(sub_row_count) - vector_b(row_count) * multiplier);
			matrix_A.setRow(sub_row_count, current_sub_row);
		}		
	}
	const unsigned& num_of_vars = a_cols;
	Vector result(num_of_vars);
	for (unsigned i = 0; i < b_len; i++)
	{
		result.setElement(column_permute[i], vector_b(i));
	}
	return result;
}
