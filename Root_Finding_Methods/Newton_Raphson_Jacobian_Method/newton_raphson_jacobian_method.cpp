#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

#define n 3

void cofactor(double matrix[n][n], double temp3[n][n], int a, int b, int c)
{
    int i = 0, j = 0;

    for(int row = 0; row < c; row++)
    {
        for(int col = 0; col < c; col++)
        {
            if(row != a && col != b)     // Assigning the minor elements of [matrix] into [temp] for a particular element in [matrix].
            {
                temp3[i][j++] = matrix[row][col];
                if(j == c-1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double determinant(double matrix[n][n], int x)
{
    double D = 0, temp2[n][n];

    if(x == 1)     // Flagging value for the recursive program.
    {
        return matrix[0][0];
    }
    int s2 = 1;

    for(int i = 0; i < x; i++)
    {
        cofactor(matrix, temp2, 0, i, x);
        D += s2*matrix[0][i]*determinant(temp2, x-1);     // Finding the determinants of the minors of first row.
        s2 = -1*s2;     // Changing the sign value for next iteration.
    }

    return D;
}

void adjoint(double matrix[n][n], double adj[n][n])
{
    int s1 = 1;
    double temp1[n][n];     // [temp1] is used to store the minors.

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cofactor(matrix, temp1, i, j, n);     // Finding the cofactor of [matrix].
            if(((i+j)%2) == 0)     // If sum of (i+j) is even, the sign value 's' is positive.
            {
                s1 = 1;
            }
            else
            {
                s1 = -1;
            }
            adj[j][i] = s1*(determinant(temp1, n-1));
        }
    }
}

void inverse_mat(double matrix[n][n], double inverse[n][n])
{
    double det = determinant(matrix, n);     // Finding the determinant of [matrix].
    double adj[n][n];

    adjoint(matrix, adj);     // Finding the adjoint of [matrix].

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            inverse[i][j] = adj[i][j]/det;
        }
    }

}

double f1(double x1, double x2, double x3)
{
    return (x1 + x2 + x3 - 3);
}

double f2(double x1, double x2, double x3)
{
    return (pow(x1, 2) + pow(x2, 2) + pow(x3, 2) - 5);
}

double f3(double x1, double x2, double x3)
{
    return (exp(x1) + x1 * x2 - x1 * x3 - 1);
}

void NRJ(double x[n], int k)
{
    double J_inv[n][n], temp[n];

    for(int m = 1; m <= k; m++)
    {
        double J[n][n] = {{1, 1, 1}, {2 * x[0], 2 * x[1], 2 * x[2]}, {exp(x[0]) + x[1] - x[2], x[0], -1 * x[0]}} , f[n] = {f1(x[0], x[1], x[2]), f2(x[0], x[1], x[2]), f3(x[0], x[1], x[2])};
        inverse_mat(J, J_inv);
        for(int i = 0; i < n; i++)
        {
            temp[i] = 0;
            for(int j = 0; j < n; j++)
            {
                temp[i] += J_inv[i][j] * f[j];
            }
            x[i] -= temp[i];
        }
        cout << "iteration: " << m << "     x: " << x[0] << "     y: " << x[1] << "     z: " << x[2] << "     f1: " << f1(x[0], x[1], x[2]) << "     f2: " << f2(x[0], x[1], x[2]) << "     f3: " << f3(x[0], x[1], x[2]) << endl;
    }
}

int main()
{
    double x[n] = {0.1, 1.2, 2.5};     // Initial guess, case 1
    // double x[n] = {1, 0, 1};     // Initial guess, case 2
    int iterations;
    cout << "Enter number of iterations: "; cin >> iterations; cout << endl;

    cout.precision(5);
    cout.setf(ios::fixed);

    NRJ(x, iterations);     // Newton Raphson Jacobian method

    cout << "\nValue of x1: " << x[0] << endl;
    cout << "Value of x2: " << x[1] << endl;
    cout << "Value of x3: " << x[2] << endl;

    return 0;
}
