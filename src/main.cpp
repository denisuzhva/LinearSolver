#include <iostream>
#include <time.h>
#include "../include/linear.h"



int main()
{
	std::cout << "It Just Works" << std::endl;

	clock_t tStart = clock();
	clock_t tLog;

	unsigned rows = 3;
	unsigned cols = 3;

	float** arr_2d = new float*[rows];
	for(unsigned i = 0; i < rows; i++)
	{
		arr_2d[i] = new float[cols];
	}

	arr_2d[0][0] = 1.0f;
	arr_2d[0][1] = 2.0f;
	arr_2d[0][2] = 3.0f;
	arr_2d[1][0] = 2.0f;
	arr_2d[1][1] = 3.0f;
	arr_2d[1][2] = 1.0f;
	arr_2d[2][0] = 3.0f;
	arr_2d[2][1] = 1.0f;
	arr_2d[2][2] = 2.0f;
	Matrix mat_A(rows, cols, arr_2d);
	
	for(unsigned i = 0; i < rows; i++)
		delete[] arr_2d[i];
	delete[] arr_2d;

	unsigned len = 3;
	float* arr_1d = new float[len];
	arr_1d[0] = 2.0f;
	arr_1d[1] = 3.0f;
	arr_1d[2] = 4.0f;
	Vector vect_b(len, arr_1d);
	std::cout << "A:" << std::endl;
	mat_A.printMatrix();
	std::cout << "b:" << std::endl;
	vect_b.printVector();

	Vector solution(3);
	solution = solveLinEq(mat_A, vect_b);
	std::cout << "x:" << std::endl;	
	solution.printVector();


	std::cout << "\nDone! Execution time: " << (float)(clock() - tStart)/CLOCKS_PER_SEC << " sec." <<  std::endl;
	return 0;
}
