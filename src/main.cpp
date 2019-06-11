#include <iostream>
#include "../include/matrix.h"


int main()
{
	std::cout << "It Just Works" << std::endl;

	uint rows = 2;
	uint cols = 2;

	float **arr_2d = new float*[rows];
	for(usint i = 0; i < rows; i++)
		float *arr_2d = new float[cols];

	arr_2d[0][0] = 1;
	arr_2d[0][1] = 2;
	arr_2d[1][0] = 3;
	arr_2d[1][1] = 7;

	Matrix mat1(rows, cols, arr_2d);
	mat1.printMatrix();

	delete arr_2d;
	return 0;
}
