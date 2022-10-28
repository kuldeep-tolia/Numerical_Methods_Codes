#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

double diff_coeff = 1.0;

double S(double x1)
{
    return (-exp(-x1) * (pow(x1, 2) - (4 * x1) + 2));
}

double T_steady(double x2)
{
    return (pow(x2, 2) * exp(-x2));
}

void Explicit_time_2CDS(double dx, double dt, double alpha)
{
    double F = alpha * dt / pow(dx, 2);
    int n = 15 / dx, i, iter, iter_max = 100000, c;     // L = 15
    double T[n+1], T_old[n+1], T_s[n+1], x[n+1];
    double tolerance = 1e-8;

    cout.setf(ios::fixed);

    x[0] = 0.0;     // Setting the initial location of x as origin

    for(i = 1; i <= n; i++)
    {
        x[i] = x[i-1] + dx;
    }

    // Computing the temperature distribution at steady state
    for(i = 0; i <= n; i++)
    {
        T_s[i] = T_steady(x[i]);
    }

    // Setting Initial Condition
    for(i = 0; i <= n; i++)
    {
        T[i] = 0;
        T_old[i] = 0;
    }

    for(iter = 1; iter <= iter_max; iter++)
    {
        for(i = 1; i < n; i++)
        {
            T[i] = (F * T[i-1]) + ((1 - (2 * F)) * T[i]) + (F * T[i+1]) + (dt * S(x[i]));
        }

        if(iter == 1)     // Setting Boundary Conditions
        {
            T[0] = 0;
            T[n] = T_steady(15.0);
        }

        c = 0;     // Setting the counter to break the main loop if all values for error are less than tolerance value
        for(i = 1; i < n; i++)
        {
            if(fabs(T[i] - T_old[i]) <= tolerance)
            {
                c += 1;
            }
        }
        if(c == (n - 1)) break;

        for(i = 0; i <= n; i++)
        {
            T_old[i] = T[i];
        }
    }

    cout << "After " << iter << " number of time steps, following results are obtained:\n\n";
    cout << "i\t\tT_numerical\t\tT_steady\n";
    for(i = 0; i <= n; i++)
    {
        cout << i << "\t\t" << setprecision(8) << T[i] << "\t\t" << setprecision(8) << T_s[i] << endl;
    }
}

void Implicit_time_2CDS(double dx, double dt, double alpha)
{
    double F = alpha * dt / pow(dx, 2);
    int n = 15 / dx, i, iter, iter_max = 100000, z;     // L = 15
    double T[n+1], T_old[n+1], T_s[n+1], x[n+1], a[n-1], b[n-1], c[n-1], d[n-1], P[n-1], Q[n-1];
    double tolerance = 1e-8;

    cout.setf(ios::fixed);

    x[0] = 0.0;     // Setting the initial location of x as origin

    for(i = 1; i <= n; i++)
    {
        x[i] = x[i-1] + dx;
    }

    // Computing the temperature distribution at steady state
    for(i = 0; i <= n; i++)
    {
        T_s[i] = T_steady(x[i]);
    }

    // Setting Initial Condition
    for(i = 0; i <= n; i++)
    {
        T[i] = 0;
        T_old[i] = 0;
    }

    // Setting the 3 arrays of coefficient matrix for a TDMA system
    for(i = 0; i <= (n-2); i++)
    {
        b[i] = 1 + (2 * F);
        if(i == 0)
        {
            a[i] = 0;
        }
        else
        {
            a[i] = -F;
        }
        if(i == (n-2))
        {
            c[i] = 0;
        }
        else
        {
            c[i] = -F;
        }
    }

    for(iter = 1; iter <= iter_max; iter++)
    {
        // Setting the 4th array of known vector for a TDMA system
        for(i = 0; i <= (n-2); i++)
        {
            if(i == 0)
            {
                d[i] = (F * T[0]) + T[1] + (S(x[1]) * dt);
            }
            else if(i == (n-2))
            {
                d[i] = (F * T[n]) + T[n-1] + (S(x[n-1]) * dt);
            }
            else
            {
                d[i] = T[i+1] + (S(x[i+1]) * dt);
            }
        }

        // Resetting P[i] and Q[i] to zero from time step to time step
        for(i = 0; i <= (n-2); i++)
        {
            P[i] = 0;
            Q[i] = 0;
        }

        // Forward Elimination for TDMA system
        for(i = 0; i <= (n-2); i++)
        {
            if(i == 0)
            {
                P[i] = -c[i] / b[i];
                Q[i] = d[i] / b[i];
            }
            else
            {
                P[i] = -c[i] / (b[i] + a[i] * P[i-1]);
                Q[i] = (d[i] - a[i] * Q[i-1]) / (b[i] + a[i] * P[i-1]);
            }
        }

        // Backward Substitution for TDMA system
        for(i = (n-2); i >= 0; i--)
        {
            if(i == (n-2))
            {
                T[i+1] = Q[i];
            }
            else
            {
                T[i+1] = P[i] * T[i+2] + Q[i];
            }
        }

        if(iter == 1)     // Setting Boundary Conditions
        {
            T[0] = 0;
            T[n] = T_steady(15.0);
        }

        z = 0;     // Setting the counter to break the main loop if all values for error are less than tolerance value
        for(i = 1; i < n; i++)
        {
            if(fabs(T[i] - T_old[i]) <= tolerance)
            {
                z += 1;
            }
        }
        if(z == (n - 1)) break;

        for(i = 0; i <= n; i++)
        {
            T_old[i] = T[i];
        }
    }

    cout << "After " << iter << " number of time steps, following results are obtained:\n\n";
    cout << "i\t\tT_numerical\t\tT_steady\n";
    for(i = 0; i <= n; i++)
    {
        cout << i << "\t\t" << setprecision(8) << T[i] << "\t\t" << setprecision(8) << T_s[i] << endl;
    }
}

void Crank_Nicolson(double dx, double dt, double alpha)
{
    double F = alpha * dt / (2 * pow(dx, 2));
    int n = 15 / dx, i, iter, iter_max = 100000, z;     // L = 15
    double T[n+1], T_old[n+1], T_s[n+1], x[n+1], a[n-1], b[n-1], c[n-1], d[n-1], P[n-1], Q[n-1];
    double tolerance = 1e-8;

    cout.setf(ios::fixed);

    x[0] = 0.0;     // Setting the initial location of x as origin

    for(i = 1; i <= n; i++)
    {
        x[i] = x[i-1] + dx;
    }

    // Computing the temperature distribution at steady state
    for(i = 0; i <= n; i++)
    {
        T_s[i] = T_steady(x[i]);
    }

    // Setting Initial Condition
    for(i = 0; i <= n; i++)
    {
        T[i] = 0;
        T_old[i] = 0;
    }

    // Setting the 3 arrays of coefficient matrix for a TDMA system
    for(i = 0; i <= (n-2); i++)
    {
        b[i] = 1.0 + (2.0 * F);
        if(i == 0)
        {
            a[i] = 0;
        }
        else
        {
            a[i] = -F;
        }
        if(i == (n-2))
        {
            c[i] = 0;
        }
        else
        {
            c[i] = -F;
        }
    }

    for(iter = 1; iter <= iter_max; iter++)
    {
        // Setting the 4th array of known vector for a TDMA system
        for(i = 0; i <= (n-2); i++)
        {
            if(i == 0)
            {
                d[i] = (F * T[0] * 2) + (T[1] * (1 - 2 * F)) + (F * T[2]) + (S(x[1]) * dt);
            }
            else if(i == (n-2))
            {
                d[i] = (F * T[n-2]) + (T[n-1] * (1 - 2 * F)) + (F * T[n]) + (F * T_steady(15.0)) + (S(x[n-1]) * dt);
            }
            else
            {
                d[i] = (F * T[i]) + (T[i+1] * (1 - 2 * F)) + (F * T[i+2]) + (S(x[i+1]) * dt);
            }
        }

        // Resetting P[i] and Q[i] to zero from time step to time step
        for(i = 0; i <= (n-2); i++)
        {
            P[i] = 0;
            Q[i] = 0;
        }

        // Forward Elimination for TDMA system
        for(i = 0; i <= (n-2); i++)
        {
            if(i == 0)
            {
                P[i] = -c[i] / b[i];
                Q[i] = d[i] / b[i];
            }
            else
            {
                P[i] = -c[i] / (b[i] + a[i] * P[i-1]);
                Q[i] = (d[i] - a[i] * Q[i-1]) / (b[i] + a[i] * P[i-1]);
            }
        }

        // Backward Substitution for TDMA system
        for(i = (n-2); i >= 0; i--)
        {
            if(i == (n-2))
            {
                T[i+1] = Q[i];
            }
            else
            {
                T[i+1] = P[i] * T[i+2] + Q[i];
            }
        }

        if(iter == 1)     // Setting Boundary Conditions
        {
            T[0] = 0;
            T[n] = T_steady(15.0);
        }

        z = 0;     // Setting the counter to break the main loop if all values for error are less than tolerance value
        for(i = 1; i < n; i++)
        {
            if(fabs(T[i] - T_old[i]) <= tolerance)
            {
                z += 1;
            }
        }
        if(z == (n - 1)) break;

        for(i = 0; i <= n; i++)
        {
            T_old[i] = T[i];
        }
    }

    cout << "After " << iter << " number of time steps, following results are obtained:\n\n";
    cout << "i\t\tT_numerical\t\tT_steady\n";
    for(i = 0; i <= n; i++)
    {
        cout << i << "\t\t" << setprecision(8) << T[i] << "\t\t" << setprecision(8) << T_s[i] << endl;
    }
}

int main()
{
    double delta_x1 = 1.0, delta_x2 = 0.1, delta_t = 0.005;

    cout << "Explicit Euler with 2-CDS\n";
    cout << "For dx = 1.0, dt = 0.005, alpha = 1.0\n";
    Explicit_time_2CDS(delta_x1, delta_t, diff_coeff);
    cout << "\n\nExplicit Euler with 2-CDS\n";
    cout << "For dx = 0.1, dt = 0.005, alpha = 1.0\n";
    Explicit_time_2CDS(delta_x2, delta_t, diff_coeff);
    cout << "\n\nImplicit Euler with 2-CDS\n";
    cout << "For dx = 1.0, dt = 0.005, alpha = 1.0\n";
    Implicit_time_2CDS(delta_x1, delta_t, diff_coeff);
    cout << "\n\nImplicit Euler with 2-CDS\n";
    cout << "For dx = 0.1, dt = 0.005, alpha = 1.0\n";
    Implicit_time_2CDS(delta_x2, delta_t, diff_coeff);
    cout << "\n\nCrank Nicolson method\n";
    cout << "For dx = 1.0, dt = 0.005, alpha = 1.0\n";
    Crank_Nicolson(delta_x1, delta_t, diff_coeff);
    cout << "\n\nCrank Nicolson method\n";
    cout << "For dx = 0.1, dt = 0.005, alpha = 1.0\n";
    Crank_Nicolson(delta_x2, delta_t, diff_coeff);

    // Extra iterations test for part - (ii)

    // Test for Euler Implicit method
    /*cout << "\n\nImplicit Euler with 2-CDS\n";
    cout << "For dx = 1.0, dt = 0.005, alpha = 1.0\n";
    Implicit_time_2CDS(1.0, 0.005, 1.0);
    cout << "\n\nFor dx = 1.0, dt = 0.05, alpha = 1.0\n";
    Implicit_time_2CDS(1.0, 0.05, 1.0);
    cout << "\n\nFor dx = 1.0, dt = 0.5, alpha = 1.0\n";
    Implicit_time_2CDS(1.0, 0.5, 1.0);
    cout << "\n\nFor dx = 1.0, dt = 1.0, alpha = 1.0\n";
    Implicit_time_2CDS(1.0, 1.0, 1.0);*/

    // Test for Crank Nicolson method
    /*cout << "\n\nCrank Nicolson method\n";
    cout << "For dx = 1.0, dt = 0.005, alpha = 1.0\n";
    Crank_Nicolson(1.0, 0.005, 1.0);
    cout << "\n\nFor dx = 1.0, dt = 0.05, alpha = 1.0\n";
    Crank_Nicolson(1.0, 0.05, 1.0);
    cout << "\n\nFor dx = 1.0, dt = 0.5, alpha = 1.0\n";
    Crank_Nicolson(1.0, 0.5, 1.0);
    cout << "\n\nFor dx = 1.0, dt = 1.0, alpha = 1.0\n";
    Crank_Nicolson(1.0, 1.0, 1.0);*/


    return 0;
}
