#ifndef MATRIX_H
#define MATRIX_H



class Matrix
{	
	private:		

		uint rows, cols;
		float **matrix;
	
	public:
	
		Matrix(uint, uint, float**);
		Matrix(uint, uint, const float&);
		Matrix(uint, uint);
		Matrix(const Matrix&);
		virtual ~Matrix();
		uint getNumOfRows() const;
		uint getNumOfCols() const;
		void printMatrix() const;

		//float& operator()(const uint&, const uint&);
		const float& operator()(const uint&, const uint&) const; 

		Matrix& operator=(const Matrix&);
		Matrix operator+(const Matrix&);
		Matrix& operator+=(const Matrix&);
		Matrix operator-(const Matrix&);
		Matrix& operator-=(const Matrix&);
		Matrix operator*(const Matrix&);
		Matrix& operator*=(const Matrix&);

		Matrix getRow(uint) const;
		Matrix getCol(uint) const;
		Matrix deleteRow(uint) const;
		Matrix deleteCol(uint) const;
		float determinant() const;

		void allocMem();
		void deallocMem();
};



#endif 
