#ifndef LINEARSOLVER_H
#define LINEARSOLVER_H
#include "./matrix.h"
#include "./vector.h"
#include "./cusmath.h"



Vector operator*(const Matrix&, const Vector&);
Vector operator*(const Vector&, const Matrix&);

Vector solveLinEq(Matrix, Vector);



#endif
