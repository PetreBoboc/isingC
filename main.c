#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "ising.h"

int main(int argc, char *argv[])
{

    int n = atoi(argv[1]); // grid size
    double J = atof(argv[2]); // J constant
    char *cond = argv[3]; // abc or pbc

    if (J == 0) { exit(0); }
     
    int border = 0;

    if ( strcmp(cond,"pbc") == 0 ) { border = 1; } // periodical boundry condition
    else if( strcmp(cond,"abc") == 0 ) {border = 0; } // absorbtion boundry condition
    else exit(0);

    int i, j, ath; // iteration variables
    double r; // random value

    int *spin[n];
    for (i = 0; i < n; i++)
        spin[i] = (int*)malloc(n*sizeof(int));

    srand(time(NULL));

    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    {
        r = ((double) rand() / (RAND_MAX));
        if (r >= 0.5) { spin[i][j]=1; }
        else { spin[i][j]=-1; }
    }

    FILE *lat1;
    lat1 = fopen("lat1.txt","w");

    fprintf(lat1,"%i\n",n);

    for (i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        fprintf(lat1,"%i ",spin[i][j]);
        fprintf(lat1,"\n");
    }
    fclose(lat1);

    double deltaE = 0; // deltaE
    double mag = 0; // magnetization

    double R = 0;
    double z = 0;

    double tStop = 0.1, tStart = 10;

    int ii = 0, jj = 0; // random generated pozitions

    float precentage; // precentage for command line

    FILE *x;
    x = fopen("x.txt","w");

    FILE *y;
    y = fopen("y.txt","w");

    while ( tStart > tStop )
    {
        mag = 0;

        for(ath = 0; ath < 256*n; ath++)
        {

            ii = rand()%(n)+0;
            jj = rand()%(n)+0;

            deltaE = J*4*spin[ii][jj]*neighbors(ii, jj, n, spin, border);

            R = exp(-deltaE / (K*tStart));
            z = ((double) rand() / (RAND_MAX));

            if (z < R)
            {
                spin[ii][jj] = -spin[ii][jj];
            }

            ii = jj = 0;

            for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
            {
                mag = mag + spin[ii][jj];
            }

        }

        mag = (double)mag / (double)(256*n);

        fprintf(x,"%f\n",tStart);
        fprintf(y,"%f\n",mag);

        mag = 0;

        precentage = (tStart - 0.1) / (10 - 0.1);

        printf("%.2f%%\n",100 - precentage*100);

        z = 0;
        tStart = tStart - 0.1;

    }

    fclose(x);
    fclose(y);

    FILE *lat2;

    lat2 = fopen("lat2.txt","w");

    for( i = 0; i < n; i++)
    {
        for( j = 0; j < n; j++)
        fprintf(lat2,"%i ",spin[i][j]);
        fprintf(lat2,"\n");
    }

    fclose(lat2);

    system("octave-cli --persist showMatrix.m");

}