#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x)
{
    const double pi = 3.1415926535;
    return (cos((pi * (x + 1)) / 8) + (0.148 * x) - 0.9062);
}

void check_roots()
{
    double x1 = -1, x2 = 0, x3 = 1;

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

double bisection_method(double a, double b)
{
    double epsilon = 1e-08, c, fa, fb, fc;
    int i = 1;
    cout.precision(6);
    cout.setf(ios::fixed);

    while(fabs(a - b) >= epsilon)
    {
        c = (a + b) / 2.0;
        fa = f(a);
        fb = f(b);
        fc = f(c);
        cout << "iteration = " << i << ": a = " << a << " , f(a) = " << fa << " , b = " << b << " , f(b) = " << fb << " , c = " << c << " , f(c) = " << fc << "\n";
        if(fc == 0)
        {
            cout << "\nThe root of the equation is " << c;
            break;
        }
        if((fa * fc) > 0)
        {
            a = c;
        }
        else if((fa * fc) < 0)
        {
            b = c;
        }
        i += 1;
    }
    return c;
}

int main()
{
    double a = -1, b = 0, result;

    check_roots();     // Showing the roots are present in the interval [-1, 0] and [0, 1].

    cout << "\nInitial guess values are " << a << " and " << b << ".\n\n";

    result = bisection_method(a, b);

    cout << "\nThe negative root of the equation is " << result << endl;

    return 0;
}
