#ifndef MATRIX_H
#define MATRIX_H
#include "../cusmath.h"



class Matrix
{	
private:		

	unsigned rows, cols;
	float **matrix;

public:

	Matrix(unsigned, unsigned, float**);
	Matrix(unsigned, unsigned, float);
	Matrix(unsigned, unsigned);
	Matrix(const Matrix&);
	virtual ~Matrix();

	const unsigned& getNumOfRows() const;
	const unsigned& getNumOfCols() const;
	void printMatrix() const;
	Matrix getRow(unsigned) const;
	Matrix getCol(unsigned) const;
	void setRow(unsigned, const Matrix&);
	void setCol(unsigned, const Matrix&);
	Matrix deleteRow(unsigned) const;
	Matrix deleteCol(unsigned) const;
	void swapRows(unsigned, unsigned);
	void swapCols(unsigned, unsigned);
	const float& operator()(unsigned, unsigned) const; 
	float& operator()(unsigned, unsigned); 

	Matrix& operator=(const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix operator*(float);
	Matrix& operator*=(float);
	Matrix operator/(float);
	Matrix& operator/=(float);

	Matrix transpose();


	//Matrix invertMatrix();
	void makeGaussElimR();
	//Matrix makeL() const;
	void makeGramSchmidtQ();
	
	//unsigned rank() const;
	float determinant() const;
	float sumOfSquares() const; 

	void allocMem();
	void deallocMem();
};



#endif 
