#include <iostream>
#include "../include/vector.h"
#include "../include/cusmath.h"



/// Construct and Destruct
// Constructor
Vector::Vector(unsigned in_len, float* in_vector) : 
	len(in_len)
{
	allocMem();
	for (unsigned i = 0; i < len; i++)
		vector[i] = in_vector[i];
}


// Copy
Vector::Vector(unsigned in_len, float val) : 
	len(in_len)
{
	allocMem();
	for (unsigned i = 0; i < len; i++)
		vector[i] = val;
}


// Copy 2
Vector::Vector(unsigned in_len) : 
	len(in_len)
{
	allocMem();
	for (unsigned i = 0; i < len; i++)
		vector[i] = 0.0f;
}


// Conversion
Vector::Vector(const Vector& vector_right) :
	len(vector_right.len)
{
	allocMem();
	for (unsigned i = 0; i < len; i++)
		vector[i] = vector_right.vector[i];
}


// Destructor with delete
Vector::~Vector() 
{
	deallocMem();
}



/// Access
// Get the length
unsigned Vector::getLen() const
{
	return len;
}


// Print the vector
void Vector::printVector() const
{
	std::cout << "(";
	for (unsigned i = 0; i < len; i++)
	{
		std::cout << vector[i];
		if (i != len-1)
			std::cout << ", ";
	}
	std::cout << ")" << std::endl;
}


// Get an element by its index
const float& Vector::getElement(unsigned ind) const 
{
	return vector[ind];
}


// Set an element of an index
void Vector::setElement(unsigned ind, float set_num)
{
	vector[ind] = set_num;
}


// Delete an element
Vector Vector::deleteElement(unsigned ind) const 
{
	if (len == 0)
	{
		std::cout << "[ERROR]: a single element cannot be deleted" << std::endl;
		return *this;
	}
	Vector result(len-1);
	for (unsigned i = 0; i < ind; i++)
		result.setElement(i, vector[i]);
	for (unsigned i = ind; i < len-1; i++)
		result.setElement(i, vector[i+1]);
	return result;
}


// Swap two elements 
void Vector::swapElements(unsigned ind1, unsigned ind2)
{
	float temp = vector[ind1];
	vector[ind1] = vector[ind2];
	vector[ind2] = temp;
}


// Access an element by its index
const float& Vector::operator()(unsigned ind) const
{
	return vector[ind];
}



/// Arithmetic operations
// Vector assignment
Vector& Vector::operator=(const Vector& vector_right)
{
	if (&vector_right == this)
	{
    		return *this;
	}
	deallocMem();
	len = vector_right.getLen();
	allocMem();
	for (unsigned i = 0; i < len; i++)
	{
		vector[i] = vector_right.vector[i];
	}
	return *this;
}


// Add two vectors
Vector Vector::operator+(const Vector& vector_right)
{
	if (len != vector_right.getLen())
	{
		std::cout << "[ERROR]: the lengths of A and B must match when C := A + B" << std::endl;
		return *this;
	}
	else
	{
		Vector result(len);
		for (unsigned i = 0; i < len; i++)
			result.vector[i] = vector[i] + vector_right.vector[i];
		return result;
	}
}


// Add to a vector
Vector& Vector::operator+=(const Vector& vector_right)
{
	if (len != vector_right.getLen()) 
	{
		std::cout << "[ERROR]: the lengths of A and B must match when A := A + B" << std::endl;
		return *this;
	}
	else
	{
		for (unsigned i = 0; i < len; i++)
			vector[i] += vector_right.vector[i];
		return *this;
	}
}


// Subtract two vectors
Vector Vector::operator-(const Vector& vector_right)
{
	if (len != vector_right.getLen())
	{
		std::cout << "[ERROR]: the lengths of A and B must match when C := A - B" << std::endl;
		return *this;
	}
	else
	{
		Vector result(len);
		for (unsigned i = 0; i < len; i++)
			result.vector[i] = vector[i] - vector_right.vector[i];
		return result;
	}
}


// Subtract from a vector
Vector& Vector::operator-=(const Vector& vector_right)
{
	if (len != vector_right.getLen())
	{
		std::cout << "[ERROR]: the lengths of A and B must match when A := A - B" << std::endl;
		return *this;
	}
	else
	{
		for (unsigned i = 0; i < len; i++)
			vector[i] -= vector_right.vector[i];
		return *this;
	}
}


// Inner product
float Vector::operator*(const Vector& vector_right)
{
	if (len != vector_right.getLen())
	{
		std::cout << "[ERROR]: the lengths of A and B must match when A := A * B" << std::endl;
		return 0;
	} 
	else
	{		
		float result = 0;
		for (unsigned i = 0; i < len; i++)
			result += vector[i] * vector_right.vector[i];
		return result;
	}
}


// Multiply a vector by a scalar
Vector Vector::operator*(float float_right)
{
	Vector result(len);
	for (unsigned i = 0; i < len; i++)
		result.vector[i] = vector[i] * float_right;
	return result;
}


// Multiply self by a scalar
Vector& Vector::operator*=(float float_right)
{
	for (unsigned i = 0; i < len; i++)
		vector[i] *= float_right;
	return *this;
}


// Divide a vector by a scalar 
Vector Vector::operator/(float float_right)
{
	Vector result(len);
	for (unsigned i = 0; i < len; i++)
		result.vector[i] = vector[i] / float_right;
	return result;
}


// Divide self by a scalar
Vector& Vector::operator/=(float float_right)
{
	for (unsigned i = 0; i < len; i++)
		vector[i] /= float_right;
	return *this;
}



/// Vector operations
// Normalize
void Vector::normalize()
{
	float divisor = (*this) * (*this);
	divisor = cusInvSqrt(divisor);
	*this *= divisor;
}


/// Misc
// Allocate memory for a vector
void Vector::allocMem()
{
	vector = new float[len];
}


// Deallocate memory
void Vector::deallocMem()
{
	delete[] vector;
}
