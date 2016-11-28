#include "Solver.h"

void mat()
{
    Solver s(2,2);
    s.A << 1 ,5, -1, 2;
    s.B << 3, 5;
    s.Print();
    s.Solve();
    cout << s.X;

}

int main()
{
    mat();
}