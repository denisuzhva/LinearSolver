#ifndef MATRIX_H
#define MATRIX_H



class Matrix
{	
private:		

	unsigned rows, cols;
	float **matrix;

public:

	Matrix(unsigned, unsigned, float**);
	Matrix(unsigned, unsigned, const float&);
	Matrix(unsigned, unsigned);
	Matrix(const Matrix&);
	virtual ~Matrix();

	unsigned getNumOfRows() const;
	unsigned getNumOfCols() const;
	void printMatrix() const;

	//float& operator()(const unsigned, const unsigned);
	const float& operator()(const unsigned&, const unsigned&) const; 

	Matrix& operator=(const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix operator*(const float&);
	Matrix& operator*=(const float&);
	Matrix operator/(const float&);
	Matrix& operator/=(const float&);

	Matrix transpose();

	Matrix getRow(unsigned) const;
	Matrix getCol(unsigned) const;
	void setRow(unsigned, const Matrix&);
	void setCol(unsigned, const Matrix&);
	Matrix deleteRow(unsigned) const;
	Matrix deleteCol(unsigned) const;
	void swapRows(unsigned, unsigned);
	void swapCols(unsigned, unsigned);

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
