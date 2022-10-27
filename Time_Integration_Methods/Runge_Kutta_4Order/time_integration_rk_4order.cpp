#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

#define lambda 10

using namespace std;

double fexact(double t)
{
    return(exp(-t) + ((10 - 1) * exp(-lambda * t)));
}

double f(double t, double y)
{
    return ((-lambda * (y - exp(-t))) - exp(-t));
}

double rk4(double h, double t0, double y0)
{
    double k1 = h * f(t0, y0);
    double k2 = h * f((t0 + (h / 2)), (y0 + (k1 / 2)));
    double k3 = h * f((t0 + (h / 2)), (y0 + (k2 / 2)));
    double k4 = h * f((t0 + h), (y0 + k3));

    return ((k1 + (2 * k2) + (2 * k3) + k4) / 6);
}

void h1(double told, double yold)
{
    float h1 = 0.1, ynew = 0.0, tnew = 0.0;
    int n = 0.8 / h1;
    ofstream file1;
    file1.open("h = 0.1 RK - 4th Order.txt");
    file1 << "t            y                   y-exact\n";
    file1 << 0.0 << "            " << yold << "                  " << yold;

    for(int i = 0; i <= n; i++)
    {
        ynew = yold + rk4(h1, told, yold);
        tnew = told + h1;
        file1 << "\n" << setprecision(2) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
        yold = ynew;
        told = tnew;
    }
    file1.close();
}

void h2(double told, double yold)
{
    float h2 = 0.05, ynew = 0.0, tnew = 0.0;
    int n = 0.8 / h2;
    ofstream file2;
    file2.open("h = 0.05 RK - 4th Order.txt");
    file2 << "t            y                   y-exact\n";
    file2 << 0.0 << "            " << yold << "                  " << yold;

    for(int i = 0; i <= n; i++)
    {
        ynew = yold + rk4(h2, told, yold);
        tnew = told + h2;
        file2 << "\n" << setprecision(2) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
        yold = ynew;
        told = tnew;
    }
    file2.close();
}

void h3(double told, double yold)
{
    float h3 = 0.025, ynew = 0.0, tnew = 0.0;
    int n = 0.8 / h3;
    ofstream file3;
    file3.open("h = 0.025 RK - 4th Order.txt");
    file3 << "t            y                   y-exact\n";
    file3 << 0.0 << "            " << yold << "                  " << yold;

    for(int i = 0; i <= n; i++)
    {
        ynew = yold + rk4(h3, told, yold);
        tnew = told + h3;
        file3 << "\n" << setprecision(3) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
        yold = ynew;
        told = tnew;
    }
    file3.close();
}

void h4(double told, double yold)
{
    float h4 = 0.0125, ynew = 0.0, tnew = 0.0;
    int n = 0.8 / h4;
    ofstream file4;
    file4.open("h = 0.0125 RK - 4th Order.txt");
    file4 << "t            y                   y-exact\n";
    file4 << 0.0 << "            " << yold << "                  " << yold;

    for(int i = 0; i <= n; i++)
    {
        ynew = yold + rk4(h4, told, yold);
        tnew = told + h4;
        file4 << "\n" << setprecision(4) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
        yold = ynew;
        told = tnew;
    }
    file4.close();
}

void h5(double told, double yold)
{
    float h5 = 0.00625, ynew = 0.0, tnew = 0.0;
    int n = 0.8 / h5;
    ofstream file5;
    file5.open("h = 0.00625 RK - 4th Order.txt");
    file5 << "t            y                   y-exact\n";
    file5 << 0.0 << "            " << yold << "                  " << yold;

    for(int i = 0; i <= n; i++)
    {
        ynew = yold + rk4(h5, told, yold);
        tnew = told + h5;
        file5 << "\n" << setprecision(5) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
        yold = ynew;
        told = tnew;
    }
    file5.close();
}

int main()
{
    float y0 = 10.0, t0 = 0.0;

    h1(t0, y0);
    h2(t0, y0);
    h3(t0, y0);
    h4(t0, y0);
    h5(t0, y0);

    return 0;
}
