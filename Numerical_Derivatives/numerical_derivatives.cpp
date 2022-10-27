#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

double Bi = 7.0;

double f(double x)
{
    return (Bi - (x * tan(x)));
}

double df(double x)
{
    return (-tan(x) - (x / pow(cos(x), 2)));
}

void first_derivative_order1(double dx1, double dx2, double dx3)
{
    double dx[3] = {dx1, dx2, dx3};
    int n[3], i;
    double x1 = -1.0, x2 = -1.0, x3 = -1.0;

    for(i = 0; i < 3; i++)
    {
        n[i] = 2 / dx[i];
    }

    double u1[n[0]+1], u2[n[1]+1], u3[n[2]+1], du1[n[0]+1], du2[n[1]+1], du3[n[2]+1], du_exact[n[2]+1];

    // Calculating u(x) for each grid size values
    for(i = 0; i <= n[0]; i++)
    {
        u1[i] = f(x1);
        x1 = x1 + dx[0];
    }

    for(i = 0; i <= n[1]; i++)
    {
        u2[i] = f(x2);
        x2 = x2 + dx[1];
    }

    for(i = 0; i <= n[2]; i++)
    {
        u3[i] = f(x3);
        x3 = x3 + dx[2];
    }

    // Computing first derivative for dx = 0.1
    for(i = 0; i < n[0]; i++)
    {
        du1[i] = (u1[i+1] - u1[i]) / dx[0];
    }
    du1[n[0]] = (u1[n[0]] - u1[n[0]-1]) / dx[0];
    x1 = -1.0;

    // Printing computed first derivative values for dx = 0.1
    ofstream file1;
    file1.open("Order 1 dx = 0.1.txt");
    file1 << "x          du\n";
    for(i = 0; i <= n[0]; i++)
    {
        file1 << setprecision(3) << x1 << "          " << setprecision(6) << du1[i] << endl;
        x1 = x1 + dx[0];
    }
    file1.close();

    // Computing first derivative for dx = 0.01
    for(i = 0; i < n[1]; i++)
    {
        du2[i] = (u2[i+1] - u2[i]) / dx[1];
    }
    du2[n[1]] = (u2[n[1]] - u2[n[1]-1]) / dx[1];
    x2 = -1.0;

    // Printing computed first derivative values for dx = 0.01
    ofstream file2;
    file2.open("Order 1 dx = 0.01.txt");
    file2 << "x          du\n";
    for(i = 0; i <= n[1]; i++)
    {
        file2 << setprecision(3) << x2 << "          " << setprecision(6) << du2[i] << endl;
        x2 = x2 + dx[1];
    }
    file2.close();

    // Computing first derivative for dx = 0.001
    for(i = 0; i < n[2]; i++)
    {
        du3[i] = (u3[i+1] - u3[i]) / dx[2];
    }
    du3[n[2]] = (u3[n[2]] - u3[n[2]-1]) / dx[2];
    x3 = -1.0;

    // Printing computed first derivative values for dx = 0.001
    ofstream file3;
    file3.open("Order 1 dx = 0.001.txt");
    file3 << "x          du          du-exact          u\n";
    for(i = 0; i <= n[2]; i++)
    {
        du_exact[i] = df(x3);
        file3 << setprecision(3) << x3 << "          " << setprecision(6) << du3[i] << "          " << setprecision(6) << du_exact[i] << "          " << setprecision(6) << u3[i] << endl;
        x3 = x3 + dx[2];
    }
    file3.close();
}

void first_derivative_order2(double dx1, double dx2, double dx3)
{
    double dx[3] = {dx1, dx2, dx3};
    int n[3], i;
    double x1 = -1.0, x2 = -1.0, x3 = -1.0;

    for(i = 0; i < 3; i++)
    {
        n[i] = 2 / dx[i];
    }

    double u1[n[0]+1], u2[n[1]+1], u3[n[2]+1], du1[n[0]+1], du2[n[1]+1], du3[n[2]+1], du_exact[n[2]+1];

    // Calculating u(x) for each grid size values
    for(i = 0; i <= n[0]; i++)
    {
        u1[i] = f(x1);
        x1 = x1 + dx[0];
    }

    for(i = 0; i <= n[1]; i++)
    {
        u2[i] = f(x2);
        x2 = x2 + dx[1];
    }

    for(i = 0; i <= n[2]; i++)
    {
        u3[i] = f(x3);
        x3 = x3 + dx[2];
    }

    // Computing first derivative for dx = 0.1
    for(i = 0; i < n[0]-1; i++)
    {
        du1[i] = ((4 * u1[i+1]) - (3 * u1[i]) - u1[i+2]) / (2 * dx[0]);
    }
    du1[n[0]-1] = ((-4 * u1[n[0]-2]) + (3 * u1[n[0]-1]) + u1[n[0]-3]) / (2 * dx[0]);
    du1[n[0]] = ((-4 * u1[n[0]-1]) + (3 * u1[n[0]]) + u1[n[0]-2]) / (2 * dx[0]);
    x1 = -1.0;

    // Printing computed first derivative values for dx = 0.1
    ofstream file4;
    file4.open("Order 2 dx = 0.1.txt");
    file4 << "x          du\n";
    for(i = 0; i <= n[0]; i++)
    {
        file4 << setprecision(3) << x1 << "          " << setprecision(6) << du1[i] << endl;
        x1 = x1 + dx[0];
    }
    file4.close();

    // Computing first derivative for dx = 0.01
    for(i = 0; i < n[1]-1; i++)
    {
        du2[i] = ((4 * u2[i+1]) - (3 * u2[i]) - u2[i+2]) / (2 * dx[1]);
    }
    du2[n[1]-1] = ((-4 * u2[n[1]-2]) + (3 * u2[n[1]-1]) + u2[n[1]-3]) / (2 * dx[1]);
    du2[n[1]] = ((-4 * u2[n[1]-1]) + (3 * u2[n[1]]) + u2[n[1]-2]) / (2 * dx[1]);
    x2 = -1.0;

    // Printing computed first derivative values for dx = 0.01
    ofstream file5;
    file5.open("Order 2 dx = 0.01.txt");
    file5 << "x          du\n";
    for(i = 0; i <= n[1]; i++)
    {
        file5 << setprecision(3) << x2 << "          " << setprecision(6) << du2[i] << endl;
        x2 = x2 + dx[1];
    }
    file5.close();

    // Computing first derivative for dx = 0.001
    for(i = 0; i < n[2]-1; i++)
    {
        du3[i] = ((4 * u3[i+1]) - (3 * u3[i]) - u3[i+2]) / (2 * dx[2]);
    }
    du3[n[2]-1] = ((-4 * u3[n[2]-2]) + (3 * u3[n[2]-1]) + u3[n[2]-3]) / (2 * dx[2]);
    du3[n[2]] = ((-4 * u3[n[2]-1]) + (3 * u3[n[2]]) + u3[n[2]-2]) / (2 * dx[2]);
    x3 = -1.0;

    // Printing computed first derivative values for dx = 0.001
    ofstream file6;
    file6.open("Order 2 dx = 0.001.txt");
    file6 << "x          du          du-exact\n";
    for(i = 0; i <= n[2]; i++)
    {
        du_exact[i] = df(x3);
        file6 << setprecision(3) << x3 << "          " << setprecision(6) << du3[i] << "          " << setprecision(6) << du_exact[i] << endl;
        x3 = x3 + dx[2];
    }
    file6.close();
}

void first_derivative_order4(double dx1, double dx2, double dx3)
{
    double dx[3] = {dx1, dx2, dx3};
    int n[3], i;
    double x1 = -1.0, x2 = -1.0, x3 = -1.0;

    for(i = 0; i < 3; i++)
    {
        n[i] = 2 / dx[i];
    }

    double u1[n[0]+1], u2[n[1]+1], u3[n[2]+1], du1[n[0]+1], du2[n[1]+1], du3[n[2]+1], du_exact[n[2]+1];

    // Calculating u(x) for each grid size values
    for(i = 0; i <= n[0]; i++)
    {
        u1[i] = f(x1);
        x1 = x1 + dx[0];
    }

    for(i = 0; i <= n[1]; i++)
    {
        u2[i] = f(x2);
        x2 = x2 + dx[1];
    }

    for(i = 0; i <= n[2]; i++)
    {
        u3[i] = f(x3);
        x3 = x3 + dx[2];
    }

    // Computing first derivative for dx = 0.1
    for(i = 0; i < n[0]-3; i++)
    {
        du1[i] = ((48 * u1[i+1]) - (25 * u1[i]) - (36 * u1[i+2]) + (16 * u1[i+3]) - (3 * u1[i+4])) / (12 * dx[0]);
    }
    du1[n[0]-3] = ((-48 * u1[n[0]-4]) + (25 * u1[n[0]-3]) + (36 * u1[n[0]-5]) - (16 * u1[n[0]-6]) + (3 * u1[n[0]-7])) / (12 * dx[0]);
    du1[n[0]-2] = ((-48 * u1[n[0]-3]) + (25 * u1[n[0]-2]) + (36 * u1[n[0]-4]) - (16 * u1[n[0]-5]) + (3 * u1[n[0]-6])) / (12 * dx[0]);
    du1[n[0]-1] = ((-48 * u1[n[0]-2]) + (25 * u1[n[0]-1]) + (36 * u1[n[0]-3]) - (16 * u1[n[0]-4]) + (3 * u1[n[0]-5])) / (12 * dx[0]);
    du1[n[0]] = ((-48 * u1[n[0]-1]) + (25 * u1[n[0]]) + (36 * u1[n[0]-2]) - (16 * u1[n[0]-3]) + (3 * u1[n[0]-4])) / (12 * dx[0]);
    x1 = -1.0;

    // Printing computed first derivative values for dx = 0.1
    ofstream file7;
    file7.open("Order 4 dx = 0.1.txt");
    file7 << "x          du\n";
    for(i = 0; i <= n[0]; i++)
    {
        file7 << setprecision(3) << x1 << "          " << setprecision(6) << du1[i] << endl;
        x1 = x1 + dx[0];
    }
    file7.close();

    // Computing first derivative for dx = 0.01
    for(i = 0; i < n[1]-3; i++)
    {
        du2[i] = ((48 * u2[i+1]) - (25 * u2[i]) - (36 * u2[i+2]) + (16 * u2[i+3]) - (3 * u2[i+4])) / (12 * dx[1]);
    }
    du2[n[1]-3] = ((-48 * u2[n[1]-4]) + (25 * u2[n[1]-3]) + (36 * u2[n[1]-5]) - (16 * u2[n[1]-6]) + (3 * u2[n[1]-7])) / (12 * dx[1]);
    du2[n[1]-2] = ((-48 * u2[n[1]-3]) + (25 * u2[n[1]-2]) + (36 * u2[n[1]-4]) - (16 * u2[n[1]-5]) + (3 * u2[n[1]-6])) / (12 * dx[1]);
    du2[n[1]-1] = ((-48 * u2[n[1]-2]) + (25 * u2[n[1]-1]) + (36 * u2[n[1]-3]) - (16 * u2[n[1]-4]) + (3 * u2[n[1]-5])) / (12 * dx[1]);
    du2[n[1]] = ((-48 * u2[n[1]-1]) + (25 * u2[n[1]]) + (36 * u2[n[1]-2]) - (16 * u2[n[1]-3]) + (3 * u2[n[1]-4])) / (12 * dx[1]);
    x2 = -1.0;

    // Printing computed first derivative values for dx = 0.01
    ofstream file8;
    file8.open("Order 4 dx = 0.01.txt");
    file8 << "x          du\n";
    for(i = 0; i <= n[1]; i++)
    {
        file8 << setprecision(3) << x2 << "          " << setprecision(6) << du2[i] << endl;
        x2 = x2 + dx[1];
    }
    file8.close();

    // Computing first derivative for dx = 0.001
    for(i = 0; i < n[2]-3; i++)
    {
        du3[i] = ((48 * u3[i+1]) - (25 * u3[i]) - (36 * u3[i+2]) + (16 * u3[i+3]) - (3 * u3[i+4])) / (12 * dx[2]);
    }
    du3[n[2]-3] = ((-48 * u3[n[2]-4]) + (25 * u3[n[2]-3]) + (36 * u3[n[2]-5]) - (16 * u3[n[2]-6]) + (3 * u3[n[2]-7])) / (12 * dx[2]);
    du3[n[2]-2] = ((-48 * u3[n[2]-3]) + (25 * u3[n[2]-2]) + (36 * u3[n[2]-4]) - (16 * u3[n[2]-5]) + (3 * u3[n[2]-6])) / (12 * dx[2]);
    du3[n[2]-1] = ((-48 * u3[n[2]-2]) + (25 * u3[n[2]-1]) + (36 * u3[n[2]-3]) - (16 * u3[n[2]-4]) + (3 * u3[n[2]-5])) / (12 * dx[2]);
    du3[n[2]] = ((-48 * u3[n[2]-1]) + (25 * u3[n[2]]) + (36 * u3[n[2]-2]) - (16 * u3[n[2]-3]) + (3 * u3[n[2]-4])) / (12 * dx[2]);
    x3 = -1.0;

    // Printing computed first derivative values for dx = 0.001
    ofstream file9;
    file9.open("Order 4 dx = 0.001.txt");
    file9 << "x          du          du-exact\n";
    for(i = 0; i <= n[2]; i++)
    {
        du_exact[i] = df(x3);
        file9 << setprecision(3) << x3 << "          " << setprecision(6) << du3[i] << "          " << setprecision(6) << du_exact[i] << endl;
        x3 = x3 + dx[2];
    }
    file9.close();
}

int main()
{
    double deltax[3] = {0.1, 0.01, 0.001};

    first_derivative_order1(deltax[0], deltax[1], deltax[2]);
    first_derivative_order2(deltax[0], deltax[1], deltax[2]);
    first_derivative_order4(deltax[0], deltax[1], deltax[2]);

    return 0;
}
