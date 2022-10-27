#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

#define n 4

void display_mat(float matrix[n][n])
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

void init_mat(float matrix[n][n])
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void LUD(float matrix[n][n], float lower[n][n], float upper[n][n])
{
    int i, j, k;
    for(i = 0; i < n; i++)
    {
        for(j = i; j < n; j++)     // Loop to evaluate upper triangular matrix.
        {
            float sum = 0;
            for(k = 0; k < i; k++)
            {
                sum += (lower[i][k]*upper[k][j]);
            }
            upper[i][j] = matrix[i][j] - sum;
        }

        for(j = i; j < n; j++)     // Loop to evaluate lower triangular matrix.
        {
            if(i == j)
            {
                lower[i][i] = 1;     // Diagonal elements of lower triangular matrix is 1.
            }
            else
            {
                float sum = 0;
                for(k = 0; k < i; k++)
                {
                    sum += (lower[j][k]*upper[k][i]);
                }
                lower[j][i] = (matrix[j][i] - sum)/upper[i][i];
            }
        }
    }
}

void cofactor(float matrix[n][n], float temp3[n][n], int a, int b, int c)
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

float determinant(float matrix[n][n], int x)
{
    float D = 0, temp2[n][n];

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

void adjoint(float matrix[n][n], float adj[n][n])
{
    int s1 = 1;
    float temp1[n][n];     // [temp1] is used to store the minors.

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

void inverse_mat(float matrix[n][n], float inverse[n][n])
{
    float det = determinant(matrix, n);     // Finding the determinant of [matrix].
    float adj[n][n];

    adjoint(matrix, adj);     // Finding the adjoint of [matrix].

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            inverse[i][j] = adj[i][j]/det;
        }
    }

}

void matrixMultiply(float mat1[n][n], float mat2[n][n], float prod[n][n])
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            prod[i][j] = 0;
            for(int k = 0; k < n; ++k)
            {
                prod[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
}

int main()
{
    int i, j;
    float low[n][n], upp[n][n], result[n][n], low_inv[n][n], upp_inv[n][n];

    float matA[n][n] = {{3, 2, 1, 5}, {2, 3, 2, 7}, {1, 2, 2, 6}, {4, 5, 6, 5}};

    cout << "\nMatrix-A:\n\n";
    display_mat(matA);

    // Initialising the lower and upper triangular matrix elements to 0.
    init_mat(low);
    init_mat(upp);

    LUD(matA, low, upp);

    /* cout << "\nLower Triangular MAtrix-L:\n\n";
    display_mat(low);
    cout << "\nUpper Triangular MAtrix-U:\n\n";
    display_mat(upp); */

    // Finding individual inverses of [low] and [upp].
    inverse_mat(low, low_inv);
    inverse_mat(upp, upp_inv);

    /* cout << "\nInverse of Lower Triangular MAtrix:\n\n";
    display_mat(low_inv);
    cout << "\nInverse of Upper Triangular MAtrix:\n\n";
    display_mat(upp_inv); */

    matrixMultiply(upp_inv, low_inv, result);

    cout << "\nInverse of give matrix [A] is:\n\n";
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            cout << fixed << setprecision(3) << result[i][j] << "\t\t";
        }
        cout << "\n";
    }

    return 0;
}
