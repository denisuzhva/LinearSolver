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
Vector::Vector(unsigned in_len, const float& val) : 
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


// Access an element by its index (const)
const float& Vector::operator()(const unsigned& ind) const
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
		float result;
		for (unsigned i = 0; i < len; i++)
			result += vector[i] * vector_right.vector[i];
		return result;
	}
}


// Multiply a vector by a scalar
Vector Vector::operator*(const float& float_right)
{
	Vector result(len);
	for (unsigned i = 0; i < len; i++)
		result.vector[i] = vector[i] * float_right;
	return result;
}


// Multiply self by a scalar
Vector& Vector::operator*=(const float& float_right)
{
	for (unsigned i = 0; i < len; i++)
		vector[i] *= float_right;
	return *this;
}


// Divide a vector by a scalar 
Vector Vector::operator/(const float& float_right)
{
	Vector result(len);
	for (unsigned i = 0; i < len; i++)
		result.vector[i] = vector[i] / float_right;
	return result;
}


// Divide self by a scalar
Vector& Vector::operator/=(const float& float_right)
{
	for (unsigned i = 0; i < len; i++)
		vector[i] /= float_right;
	return *this;
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
