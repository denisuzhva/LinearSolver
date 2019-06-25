#ifndef VECTOR_H
#define VECTOR_H
#include "../include/cusmath.h"



class Vector
{
private:

	unsigned len;
	float *vector;

public:
	Vector(unsigned, float*);
	Vector(unsigned, float);
	Vector(unsigned);
	Vector(const Vector&);
	virtual ~Vector();

	unsigned getLen() const;
	void printVector() const;
	const float& getElement(unsigned) const;
	void setElement(unsigned, float); 
	Vector deleteElement(unsigned) const;
	void swapElements(unsigned, unsigned);
	const float& operator()(unsigned) const; 


	Vector& operator=(const Vector&);
	Vector operator+(const Vector&);
	Vector& operator+=(const Vector&);
	Vector operator-(const Vector&);
	Vector& operator-=(const Vector&);
	float operator*(const Vector&);
	Vector operator*(float);
	Vector& operator*=(float);
	Vector operator/(float);
	Vector& operator/=(float);

	void normalize();
	
	void allocMem();
	void deallocMem();

};



#endif
