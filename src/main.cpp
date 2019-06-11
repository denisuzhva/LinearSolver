#include <iostream>
#include <time.h>
#include "../include/matrix.h"



int main()
{
	std::cout << "It Just Works" << std::endl;

	clock_t tStart = clock();
	clock_t tLog;

	uint rows = 2;
	uint cols = 2;

	float** arr_2d = new float*[rows];
	for(usint i = 0; i < rows; i++)
	{
		arr_2d[i] = new float[cols];
	}

	arr_2d[0][0] = 1;
	arr_2d[0][1] = 2;
	arr_2d[1][0] = 3;
	arr_2d[1][1] = 7;

	Matrix mat1(rows, cols, arr_2d);
	mat1.printMatrix();

	delete arr_2d;
	std::cout << "\nDone! Execution time: " << (float)(clock() - tStart)/CLOCKS_PER_SEC << " sec." <<  std::endl;
	return 0;
}
