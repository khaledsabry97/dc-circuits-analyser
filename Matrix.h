#include <iostream>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

typedef Matrix<float, Eigen::Dynamic, 1> Vector;

// prototypes
class Solver
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
    MatrixXf A;
    Vector B;
    Vector X;

    const int rows, columns;

    Solver(int r, int c);

    void Print();
    void Zero();
    bool IsZero();
    Vector Solve();
};

// implementation
// public:
Solver::Solver(int r, int c) :rows(r), columns(c) 
{
    A.resize(rows, columns);
    B.resize(rows);
    X.resize(rows);

    Zero();
}

void Solver::Zero()
{
    A = MatrixXf::Zero(rows, columns);
    B = MatrixXf::Zero(rows, 1);
    X = MatrixXf::Zero(rows, 1);
}

void Solver::Print()
{
    cout << "From equation AX = B\n";
    _Print_A();
    _Print_X();
    _Print_B();
}

bool Solver::IsZero()
{
    return (_is_A_zero() && _is_B_zero() && _is_X_zero()); 
}

Vector Solver::Solve()
{
    using Eigen::ColPivHouseholderQR;

    if (_calculated)
        return X;

    X = A.colPivHouseholderQr().solve(B);
    _calculated = true;

    return X;
}


// private:
bool Solver::_is_A_zero()
{
    return (A == MatrixXf::Zero(rows, columns));
}
bool Solver::_is_B_zero()
{
    return (B == MatrixXf::Zero(rows, 1));
}
bool Solver::_is_X_zero()
{
    return (X == MatrixXf::Zero(rows, 1));
}

void Solver::_Print_X()
{
    if (!_calculated)
        cout << "X isn't calculated\n";
    else
        cout << "X:\n" << X << endl;
}
void Solver::_Print_A()
{
    if (_is_A_zero())
        cout << "A = Zero\n";
    else
        cout << "A:\n" << A << endl;
}
void Solver::_Print_B()
{
    if (_is_A_zero())
        cout << "B = Zero\n";
    else
        cout << "B:\n" << B << endl;
}
