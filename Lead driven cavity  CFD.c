#include<stdio.h>
#include<math.h>
int main(){
double L=1,H=1,delta_x,delta_y,beta,Re=400; // parameters
int imax=129,jmax=129; // imax=jmax=129 for 129 x 129 grid
delta_x=L/(imax-1);delta_y=H/(jmax-1);
beta=delta_x/delta_y;
double
si_new[imax+1][jmax+1],omega_new[imax+1][jmax+1],si_old[imax+1][jmax+1],omega_ol
d[imax+1][jmax+1],u[imax+1][jmax+1],v[imax+1][jmax+1]; // variable to store data
int i,j,k=0;
for(j=1;i<=jmax;j++){
for(i=1;i<=imax;i++){
si_old[i][j]=0;
si_new[i][j]=0;
omega_old[i][j]=0;
omega_new[i][j]=0;
u[i][j]=0;
v[i][j]=0;
// assign all variable (si,omega,u,v ) equal to zero, so random value not
assign to them
}
}
for(i=2;i<=imax-1;i++){
u[i][jmax]=1; // u value asssign at top to zero
}
for(j=1;j<=jmax;j++){
for(i=1;i<=imax;i++){
if(j==1){
omega_new[i][j]=-2*(si_new[i][j+1])/(pow(delta_y,2));
// boundary condition at y=0 (bottom wall)
}
else if(j==jmax){
omega_new[i][j]=-2*(si_new[i][j-1]+u[i][j])/(pow(delta_y,2));
// boundary condition at y=H=1 (top wall)
}
else if(i==1){
omega_new[i][j]=-2*(si_new[i+1][j])/(pow(delta_x,2));
// boundary condition at x=0 (left wall)
}
else if(i==imax){
omega_new[i][j]=-2*(si_new[i-1][j])/(pow(delta_x,2));
// boundary condition at x=L=1 (right wall)
}
else{
omega_new[i][j]=0; // inner points
}
}
} // boundary condition initialization
int itr=0; // initialize iteration count as 0
double error=pow(10,1), sum_omega=0; // any large error is assumed, ans
sum omega to store sum of all omega
while(error > pow(10,-5)){ // stoping condition ( when error < 10^-5 it
stops)
for(j=1;j<=jmax;j++){
for(i=1;i<=imax;i++){
si_old[i][j]=si_new[i][j]; // to assign new value to old
value so new calculation can be done
omega_old[i][j]=omega_new[i][j];
}
}
for(k=1;k<=10;k++){ // inner iteration of si ( 10 is
used)
for(j=2;j<=jmax-1;j++){
for(i=2;i<=imax-1;i++){
si_new[i][j]=(si_new[i+1][j]+si_new[i1][j]+pow(beta,2)*(si_new[i][j+1]+si_new[i][j-1])+ pow(delta_x,2)*omega_new[i][j]) /
(2.0*(1.0+pow(beta,2)));
// update si
}
}
}
for(j=1;j<=jmax;j++){
for(i=1;i<=imax;i++){
if(j==1){
omega_new[i][j]=-2*(si_new[i][j+1])/(pow(delta_y,2));
// boundary condition at y=0 (bottom wall)
}
else if(j==jmax){
omega_new[i][j]=-2*(si_new[i][j1]+u[i][j])/(pow(delta_y,2)); // boundary condition at y=H=1 (top wall)
}
else if(i==1){
omega_new[i][j]=-2*(si_new[i+1][j])/(pow(delta_x,2));
// boundary condition at x=0 (left wall)
}
else if(i==imax){
omega_new[i][j]=-2*(si_new[i-1][j])/(pow(delta_x,2));
// boundary condition at x=L=1 (right wall)
}
}
} // boundary condition at each iteration
for(k=1;k<=2;k++){ // inner iteration of omega ( 2 is used)
for(j=2;j<=jmax-1;j++){
for(i=2;i<=imax-1;i++){
omega_new[i][j]=(omega_new[i+1][j] +
omega_new[i-1][j] + pow(beta,2)*(omega_new[i][j+1] + omega_new[i][j-1]) -
0.25*beta*Re*(omega_new[i+1][j] - omega_new[i-1][j])*(si_new[i][j+1] - si_new[i][j-1]) +
0.25*beta*Re*(omega_new[i][j+1] - omega_new[i][j-1])*(si_new[i+1][j] - si_new[i-1][j])) /
(2.0*(1.0+pow(beta,2)));
// update omega
}
}
}
error=0;
sum_omega=0;
for(i=2;i<=jmax-1;i++){
for(j=2;j<=imax-1;j++){
error=error+fabs(omega_new[i][j]-omega_old[i][j]);
// summation | omega^(k+1) - omega^(k) | calculated
sum_omega=sum_omega+fabs(omega_new[i][j]);
// summation of | omega^(k+1) | calculated
}
}
error=error/sum_omega; // | omega^(k+1) - omega^(k) | / |
omega^(k+1) |
itr=itr+1; // increament iteration count
}
for(j=2;j<=jmax-1;j++){
for(i=2;i<=imax-1;i++){
u[i][j]=(si_new[i][j+1] - si_new[i][j-1])/(2.0*delta_y);
v[i][j]=(si_new[i+1][j] - si_new[i-1][j])/(2.0*delta_x);
}
}
FILE *OUT=fopen("lid-driven_square_cavity_data.txt","w"); // for file storage
printf("\nu-velocity along the vertical centre line\n");
fprintf(OUT,"\nu-velocity along the vertical centre line\n");
for(j=1;j<=jmax;j++){
printf("%lf\t",u[65][j]);
fprintf(OUT,"%lf\t",u[65][j]); // u-velocity along the vertical
centre line storing to file
}
printf("\nv-velocity along the horizontal centre line\n");
fprintf(OUT,"\nv-velocity along the horizontal centre line\n");
for(i=1;i<=imax;i++){
printf("%lf\t",v[i][65]);
fprintf(OUT,"%lf\t",v[i][65]); // v-velocity along the horizontal
centre line storing to file
}
printf("\nsi value\n");
fprintf(OUT,"\nsi value\n");
for(j=1;j<=jmax;j++){
for(i=1;i<=imax;i++){
printf("%lf\t",si_new[i][j]);
fprintf(OUT,"%lf\t",si_new[i][j]); // si value storing to file
}
printf("\n");
fprintf(OUT,"\n");
}
printf("\nomega value\n");
fprintf(OUT,"\nomega value\n");
for(j=1;j<=jmax;j++){
for(i=1;i<=imax;i++){
printf("%lf\t",omega_new[i][j]);
fprintf(OUT,"%lf\t",omega_new[i][j]); // omega value storing to
file
}
printf("\n");
fprintf(OUT,"\n");
}
return 0;
}
