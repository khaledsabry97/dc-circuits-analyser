#pragma once
#include <iostream>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

typedef Matrix<float, Eigen::Dynamic, 1> Vector;

// prototypes
class Equation
{
private:
    bool _calculated;

    bool _is_A_zero();
    bool _is_B_zero(); 
    bool _is_X_zero(); 

    void _Print_X();
    void _Print_B();
    void _Print_A();

public:
    MatrixXf A;
    Vector B;
    Vector X;

    const int rows, columns;

    Equation(int r, int c);

    void Print();
    void Zero();
    bool IsZero();
    Vector Solve();
};

// implementation
// public:
Equation::Equation(int r, int c) 
	:rows(r), columns(c), _calculated(false) 
{
    A.resize(rows, columns);
    B.resize(rows);
    X.resize(rows);

    Zero();
}

void Equation::Zero()
{
    A = MatrixXf::Zero(rows, columns);
    B = MatrixXf::Zero(rows, 1);
    X = MatrixXf::Zero(rows, 1);
}

void Equation::Print()
{
    cout << "From equation AX = B\n";
    _Print_A();
    _Print_X();
    _Print_B();
}

bool Equation::IsZero()
{
    return (_is_A_zero() && _is_B_zero() && _is_X_zero()); 
}

Vector Equation::Solve()
{
    using Eigen::ColPivHouseholderQR;

    if (_calculated)
        return X;

    X = A.colPivHouseholderQr().solve(B);
    _calculated = true;

    return X;
}


// private:
bool Equation::_is_A_zero()
{
    return (A == MatrixXf::Zero(rows, columns));
}
bool Equation::_is_B_zero()
{
    return (B == MatrixXf::Zero(rows, 1));
}
bool Equation::_is_X_zero()
{
    return (X == MatrixXf::Zero(rows, 1));
}

void Equation::_Print_X()
{
    if (!_calculated)
        cout << "X isn't calculated\n";
    else
        cout << "X:\n" << X << endl;
}
void Equation::_Print_A()
{
    if (_is_A_zero())
        cout << "A = Zero\n";
    else
        cout << "A:\n" << A << endl;
}
void Equation::_Print_B()
{
    if (_is_A_zero())
        cout << "B = Zero\n";
    else
        cout << "B:\n" << B << endl;
}
