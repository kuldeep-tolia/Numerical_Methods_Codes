#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

#define lambda 10

using namespace std;

double f(double t, double y)
{
    return ((-lambda * (y - exp(-t))) - exp(-t));
}

double fexact(double t)
{
    double y0 = 10.0;
    return(exp(-t) + ((y0 - 1) * exp(-lambda * t)));
}

void h1(double told, double yold)
{
    float h1 = 0.1, ynew = 0.0, tnew = 0.0;
    ofstream file1;
    file1.open("h = 0.1 Euler Explicit.txt");
    file1 << "t            y                   y-exact\n";
    file1 << 0.0 << "            " << yold << "                  " << yold;
    while(tnew < 0.8)
    {
        ynew = yold + (h1 * f(told, yold));
        yold = ynew;
        tnew = told + h1;
        told = tnew;
        file1 << "\n" << setprecision(2) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
    }
    file1.close();
}

void h2(double told, double yold)
{
    float h2 = 0.05, ynew = 0.0, tnew = 0.0;
    ofstream file2;
    file2.open("h = 0.05 Euler Explicit.txt");
    file2 << "t            y                   y-exact\n";
    file2 << 0.0 << "            " << yold << "                  " << yold;
    while(tnew < 0.8)
    {
        ynew = yold + (h2 * f(told, yold));
        yold = ynew;
        tnew = told + h2;
        told = tnew;
        file2 << "\n" << setprecision(3) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
    }
    file2.close();
}

void h3(double told, double yold)
{
    float h3 = 0.025, ynew = 0.0, tnew = 0.0;
    ofstream file3;
    file3.open("h = 0.025 Euler Explicit.txt");
    file3 << "t            y                   y-exact\n";
    file3 << 0.0 << "            " << yold << "                  " << yold;
    while(tnew < 0.8)
    {
        ynew = yold + (h3 * f(told, yold));
        yold = ynew;
        tnew = told + h3;
        told = tnew;
        if(tnew > 0.8)
        {
            break;
        }
        file3 << "\n" << setprecision(4) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
    }
    file3.close();
}

void h4(double told, double yold)
{
    float h4 = 0.0125, ynew = 0.0, tnew = 0.0;
    ofstream file4;
    file4.open("h = 0.0125 Euler Explicit.txt");
    file4 << "t            y                   y-exact\n";
    file4 << 0.0 << "            " << yold << "                  " << yold;
    while(tnew < 0.8)
    {
        ynew = yold + (h4 * f(told, yold));
        yold = ynew;
        tnew = told + h4;
        told = tnew;
        if(tnew > 0.8)
        {
            break;
        }
        file4 << "\n" << setprecision(5) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
    }
    file4.close();
}

void h5(double told, double yold)
{
    float h5 = 0.00625, ynew = 0.0, tnew = 0.0;
    ofstream file5;
    file5.open("h = 0.00625 Euler Explicit.txt");
    file5 << "t            y                   y-exact\n";
    file5 << 0.0 << "            " << yold << "                  " << yold;
    while(tnew < 0.8)
    {
        ynew = yold + (h5 * f(told, yold));
        yold = ynew;
        tnew = told + h5;
        told = tnew;
        file5 << "\n" << setprecision(5) << tnew << "          " << setprecision(8) << ynew << "          " << setprecision(8) << fexact(tnew);
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
