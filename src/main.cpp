#include <iostream>
#include <time.h>
#include "../include/matrix.h"



int main()
{
	std::cout << "It Just Works" << std::endl;

	clock_t tStart = clock();
	clock_t tLog;

	uint rows = 3;
	uint cols = 3;

	float** arr_2d = new float*[rows];
	for(unsigned short i = 0; i < rows; i++)
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
	Matrix mat1(rows, cols, arr_2d);
	mat1.printMatrix();
	std::cout << mat1.determinant() << std::endl;
	
	for(uint i = 0; i < rows; i++)
		delete[] arr_2d[i];
	delete[] arr_2d;
	std::cout << "\nDone! Execution time: " << (float)(clock() - tStart)/CLOCKS_PER_SEC << " sec." <<  std::endl;
	return 0;
}
