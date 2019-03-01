#include <stdio.h>
#include "ising.h"

double neighbors(int i, int j, int n, int** matrix, int border)
{

    int nUp = 0, nDown = 0, nLeft = 0, nRight = 0;
    int up = 0, down = 0, left = 0, right = 0;

    if (border == 1)
    {
        if ( i-1 == -1) { up = n-1; } else { up = 0; }
        if ( j-1 == -1) { left = n-1; } else { left = 0; }
        if ( i+1 == n) { down = 0; } else { down = i+1; }
        if ( j+1 == n) { right = 0; } else { right = j+1; }

        return matrix[up][j]+matrix[down][j]+matrix[i][left]+matrix[i][right];

    }

    if (border == 0)
    {
        if ( i-1 == -1 ) { nUp = 0; } else { nUp = matrix[i-1][j]; }
        if ( j-1 == -1 ) { nLeft = 0; } else { nLeft = matrix[i][j-1]; }
        if ( i+1 == n) { nDown = 0; } else { nDown = matrix[i+1][j]; }
        if ( j+1 == n) { nRight = 0; } else { nRight = matrix [i][j+1]; }

        return nUp+nDown+nLeft+nRight;

    }

    else return 0;

}