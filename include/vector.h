#ifndef VECTOR_H
#define VECTOR_H



class Vector
{
private:

	unsigned len;
	float *vector;

public:
	Vector(unsigned, float*);
	Vector(unsigned, const float&);
	Vector(unsigned);
	Vector(const Vector&);
	virtual ~Vector();

	unsigned getLen() const;
	void printVector() const;
	
	const float& operator()(const unsigned&) const; 


	Vector& operator=(const Vector&);
	Vector operator+(const Vector&);
	Vector& operator+=(const Vector&);
	Vector operator-(const Vector&);
	Vector& operator-=(const Vector&);
	float operator*(const Vector&);
	Vector operator*(const float&);
	Vector& operator*=(const float&);
	Vector operator/(const float&);
	Vector& operator/=(const float&);

	void allocMem();
	void deallocMem();

};



#endif
