#ifndef MATRIX_H
#define MATRIX_H

using uint = unsigned int;
using sint = short int;
using usint = unsigned short int;



class Matrix
{	
	private:		

		uint rows, cols;
		float **matrix;
	
	public:
	
		Matrix(uint, uint, float**);
		Matrix(uint, uint, const float&);
		virtual ~Matrix();
		uint getNumOfRows() const;
		uint getNumOfCols() const;
		void printMatrix();

		float& operator()(const uint&, const uint&);
		const float& operator()(const uint&, const uint&) const; 

		Matrix& operator=(const Matrix&);
		Matrix operator+(const Matrix&);
		Matrix& operator+=(const Matrix&);
		Matrix operator-(const Matrix&);
		Matrix& operator-=(const Matrix&);
		Matrix operator*(const Matrix&);
		Matrix& operator*=(const Matrix&);

		Matrix deleteRow(uint);
		Matrix deleteCol(uint);
		float determinant() const;

		void allocMem();
		void deallocMem();
};



#endif 
