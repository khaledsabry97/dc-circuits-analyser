#include "Eigen/Dense"
#include <iostream>
using namespace std;

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;


// prototypes
class Matrices
{
private:
    bool _calculated = false;

    bool _is_A_zero();
    bool _is_B_zero(); 
    bool _is_X_zero(); 

    void _Print_X();
    void _Print_B();
    void _Print_A();

public:
    Matrix A;
    Vector B;
    Vector X;

    const int rows, columns;

    Matrices(int r, int c);

    void Print();
    void Zero();
    bool IsZero();
    Vector Solve();
};

// implementation
// public:
Matrices::Matrices(int r, int c) :rows(r), columns(c) 
{
    A.resize(rows, columns);
    B.resize(rows);
    X.resize(rows);

    Zero();
}

void Matrices::Zero()
{
    A = Matrix::Zero(rows, columns);
    B = Matrix::Zero(rows, 1);
    X = Matrix::Zero(rows, 1);
}

void Matrices::Print()
{
    cout << "From equation AX = B\n";
    _Print_A();
    _Print_X();
    _Print_B();
}

bool Matrices::IsZero()
{
    return (_is_A_zero() && _is_B_zero() && _is_X_zero()); 
}

Vector Matrices::Solve()
{
    using Eigen::ColPivHouseholderQR;

    if (_calculated)
        return X;

    X = A.colPivHouseholderQr().solve(B);
    _calculated = true;

    return X;
}


// private:
bool Matrices::_is_A_zero()
{
    return (A == Matrix::Zero(rows, columns));
}
bool Matrices::_is_B_zero()
{
    return (B == Matrix::Zero(rows, 1));
}
bool Matrices::_is_X_zero()
{
    return (X == Matrix::Zero(rows, 1));
}

void Matrices::_Print_X()
{
    if (!_calculated)
        cout << "X isn't calculated\n";
    else
        cout << "X:\n" << X << endl;
}
void Matrices::_Print_A()
{
    if (_is_A_zero())
        cout << "A = Zero\n";
    else
        cout << "A:\n" << A << endl;
}
void Matrices::_Print_B()
{
    if (_is_A_zero())
        cout << "B = Zero\n";
    else
        cout << "B:\n" << B << endl;
}
