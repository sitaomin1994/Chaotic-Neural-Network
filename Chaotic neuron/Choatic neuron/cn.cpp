#include<stdio.h>
#include<math.h> 
#include<stdlib.h>
double f(double z,double e)
{double result;
 result=1.0/(1.0+exp(-z/e));
return result;	
}


int main(void){
	double x,y,a,e,b,k;
	
	double f(double z,double e);

	FILE *fp1;
	fp1=fopen("choatic-1.txt","w");
	b=1.000000;
	y=0.50000000;
	e=0.04000000;
	a=0.76;
	k=0.5;
	
	
	for(int t=1;t<1000;t++){
				x=f(y,e);
				y=k*y-b*f(y,e)+a;
				fprintf(fp1,"%d %lf %lf\n",t,x,y);
				
	 }
			
}

