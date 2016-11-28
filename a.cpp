#include "Matrix.h"

int main()
{
    Solver s(2,2);
    s.A << 1 ,2;
    s.B << 3, 5;
    s.Print();
    s.Solve();
    s.Print();
}