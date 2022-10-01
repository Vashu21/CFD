#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#define Nx 21
#define Ny 41
#define errmx 0.01
int main()
{
int i, j, k = 0;
/* i,j Array Index ; Nx,Ny No. of grids ; k Iteration counter*/
double bet, x[Nx], y[Ny], es = 0, err = 1, dx = 0.05, dy = 0.05, u[Nx][Ny], ukpl[Nx][Ny];
/* bet is Beta parameter ; es dummy variable for error (err) ; errmx Maximum error value ; dx,dy Grid spacing ; u Temperature array */
bet = dx / dy;
/* Temperature array declaration*/
for (i = 0; i < Nx; i++) /* BC and IC defining*/
{
for (j = 0; j < Ny; j++)
{
if (j == 0)
{
	u[i][j]=100;
}
else
{
	u[i][j]=0;
}
}
}
/* ukpl - Dummy variable to be used in difference scheme*/
for (j = 0; j < Ny; j++)
{
for (i = 0; i < Nx; i++)
{
ukpl[i][j] = u[i][j];
}
}
printf("\n i \t j \t T(Gauss Seidel) \n");
/* Initiation of iteration with specific to given condition on error*/
while (err > errmx)
{
k = k + 1;
/*printf("\n K = %d \n", k);*/ for (i = 1; i < (Nx - 1); i++)
{
for (j = 1; j < (Ny - 1); j++)
{
ukpl[i][j] = (ukpl[i + 1][j] + ukpl[i - 1][j] + (bet * bet * (ukpl[i][j + 1] + ukpl[i][j - 1]))) / (2 * (1 + (bet * bet)));
/* Gauss Seidel Scheme*/
}
}
for (i = 0; i < Nx; i++)
{
for (j = 0; j < Ny; j++)
{
es = es + fabs((ukpl[i][j] - u[i][j])); /* Error
Evaluation */
}
}
for (i = 0; i < Nx; i++)
{
for (j = 0; j < Ny; j++)
{
u[i][j] = ukpl[i][j]; /* updating u */
}
}
err = es; 
es = 0;
}
for (i = 0; i < Nx; i++)
{
for (j = 0; j < Ny; j++)
{
printf("%d \t %d \t %lf\n", i, j, u[i][j]);
/* Converged temperature values at each grid */
}
}
printf("Error is %lf \n", err);
printf("Total number of iteration = %d \n", k);
/* Grid generation to save the output */
x[0]=0.0;
y[0]=0.0;
for(j = 0; j < Ny; j++)
{
y[j+1]=y[j]+dy;
}
for(i = 0; i < Nx; i++)
{
x[i+1]=x[i]+dx;
}
FILE *g,*p;
g=fopen("Gauss_Seidal.txt","w");
fprintf(g,"Variable =\"X\",\"Y\",\"Temprature\"\n",Ny,Nx); fprintf(g,"\tI=%d\tJ=%d\n",Nx,Ny);
for(i = 0; i < Nx; i++)
{
for(j = 0; j < Ny; j++)
{
fprintf(g,"%lf\t%lf\t%lf\n",x[i],y[j],u[i][j]);
/* saving of T values into file along with grids */
}
}
fclose(g); p=fopen("Gauss_Seidal_nodes.dat","w"); for(j = 0; j < Ny; j++)
{
fprintf(p,"%d\t%d\t%lf\n",11,j+1,u[10][j]);
/* At i=11 and for all j T values */
}
fclose(p);
}
