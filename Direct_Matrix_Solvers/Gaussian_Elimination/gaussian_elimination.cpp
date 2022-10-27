#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void display_mat(int n, float **matrix)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n+1; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

void forward_elim(int n, float **matrix)
{
    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            float factor = matrix[j][i]/matrix[i][i];     // Finding the factor to make the elements below mat[i][i] as 0.
            for(int k = 0; k <= n; k++)
            {
                matrix[j][k] = matrix[j][k] - (factor*matrix[i][k]);     // Updating the subsequent row elements.
            }
        }
    }
}

void backward_sub(int n, float **matrix, float *arr)
{
    for(int i = n-1; i >= 0; i--)
    {
        arr[i] = matrix[i][n];
        for(int j = i+1; j<n; j++)
        {
            arr[i] -= matrix[i][j]*arr[j];
        }
        arr[i] = arr[i]/matrix[i][i];
    }
}

int main()
{
    int i, j, n;

    cout << "Enter the value of n: "; cin >> n; cout << "\n";     // Taking the value of n from user

    // Declaring Augmented matrix for Gaussian Elimination method, [A|B]
    float **mat = new float *[n];

    for(int i = 0; i < n; i++)
    {
        mat[i] = new float [n];
    }

    // Declaring the unknown vector, [x]
    float *x = new float [n];

    // Populating the augmented matrix elements with max(i, j) value as stated in the question.
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n+1; j++)
        {
            if(j == n)
            {
                mat[i][j] = 1;     // Assigning the right hand side vector element as 1 as stated in the question.
            }
            else
            {
                mat[i][j] = max(i+1, j+1);
            }
        }
    }

    /* cout << "The augmented matrix [A|B] to be solved using Gaussian Elimination:\n\n";     // Displaying the Augmented matrix
    display_mat(n, mat);*/

    // Performing forward elimination.
    forward_elim(n, mat);

    /* Display matrix after forward elimination operation
    cout << "\n\n";
    display_mat(n, mat); */

    // Performing backward substitution to obtain unknown vector [x].
    backward_sub(n, mat, x);

    cout << "\nThe solution vector is as follows:\n\n";
    for(i = 0; i < n; i++)
    {
        cout << "x" << i+1 << " = " << fixed << setprecision(10) << x[i] << endl;
    }

    cout << endl;
    return 0;
}
