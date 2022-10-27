#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

void exact_solution()
{
    double h = 0.1, n = 9 / h, t = 0, y_exact;
    ofstream file1;
    file1.open("Exact Solution.txt");
    file1 << "t         y-exact\n";
    for(int i = 0; i <= n; i++)
    {
        y_exact = cos(4.0 * t);
        file1 << setprecision(2) << t << "     " << setprecision(5) << y_exact << endl;
        t = t + h;
    }
    file1.close();
}

void numerical_solution()
{
    double h = 0.1, n = 9 / h, t = 0.1, y1[3], y2[3];
    y1[0] = 1; y2[0] = 0;
    ofstream file2;
    file2.open("Numerical Solution.txt");
    file2 << "t         y1          y2\n";
    file2 << "0.0       1.0         0.0\n";

    // Calculating step 1 at t = 0.1 using Explicit Euler method
    y1[1] = y1[0] + (h * y2[0]);
    y2[1] = y2[0] + (h * -16.0 * y1[0]);
    file2 << t << "       " << setprecision(5) << y1[1] << "     " << setprecision(5) << y2[1] << endl;

    // Calculating other steps using the given method in problem statement
    for(int i = 0; i < n-1; i++)
    {
        y1[2] = y1[0] + (2 * h * y2[1]);
        y2[2] = y2[0] + (2 * h * -16.0 * y1[1]);
        t = t + 0.1;
        file2 << t << "       " << setprecision(5) << y1[2] << "     " << setprecision(5) << y2[2] << endl;

        // Updating the y1 and y2 array values
        y1[0] = y1[1];
        y2[0] = y2[1];
        y1[1] = y1[2];
        y2[1] = y2[2];
    }
    file2.close();
}

int main()
{
    exact_solution();

    numerical_solution();

    return 0;
}
