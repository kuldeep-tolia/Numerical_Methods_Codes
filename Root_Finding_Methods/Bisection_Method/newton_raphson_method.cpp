#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x)
{
    return ((1 / (x + 2)) + (1 / (x + 1)) - (2 / exp(x)));
}

double df(double x)
{
    return ((2 / exp(x)) - (1 / pow(x + 2, 2)) - (1 / pow(x + 1, 2)));
}

void check_roots()
{
    double x1 = -0.9, x2 = 0, x3 = 1.0;
    cout << "When x = " << x1 << " --- f(x) = " << f(x1) << endl;
    cout << "When x = " << x2 << " --- f(x) = " << f(x2) << endl;
    cout << "When x = " << x3 << " --- f(x) = " << f(x3) << endl;
    if((f(x1) * f(x2)) < 0)
    {
        cout << "\nRoots lie between " << x1 << " and " << x2 << ".\n";
    }
    if((f(x2) * f(x3)) < 0)
    {
        cout << "Roots lie between " << x2 << " and " << x3 << ".\n";
    }
}

double newton_raphson(double u)
{
    double tolerance = 1e-06, r = f(u) / df(u);
    while(fabs(r) >= tolerance)
    {
        r = f(u) / df(u);
        u = u - r;
    }
    return u;
}

int main()
{
    check_roots();

    double guess_1 = -0.9, guess_2 = 1.0;
    // Note: For the given equation, initial value of -0.37 cannot be taken as it does not satisfy the convergence criteria.

    cout.precision(5);
    cout.setf(ios::fixed);

    guess_1 = newton_raphson(guess_1);
    guess_2 = newton_raphson(guess_2);
    cout << "\nThe roots of the given equation are " << guess_1 << " and " << guess_2 << endl;

    return 0;
}
