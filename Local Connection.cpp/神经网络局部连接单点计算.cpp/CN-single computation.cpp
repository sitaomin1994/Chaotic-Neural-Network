# include <windows.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <GL/glut.h>
# define PI 3.1415926
# define MAX_CHAR 128


double sigmod(double z,double e){
	double result;
	result=1.0/(1.0+exp(-z/e));
	return result;	
}


int main(int argc, char *argv[])
{
	double x[50][50];
	double f[50][50];
	double r[50][50];
	double y[50][50];
	double ist[50][50];
	double WeightSum[50][50];
	double	kr=0.72,kf=0.9;
    double l=10.0,o=2.0,e=0.0015;	
	double feedback=0,refractoriness=0;							//feedback 反馈项 refractoriness 不应性项
	double Wup[50][50],Wdown[50][50],Wleft[50][50],Wright[50][50];                      //Wup,Wdown,Wleft,Wright为每个神经元相邻神经元之间的连接权重 //ist:内部状态函数  t:时间  kf反馈系数 
	double MAX,MIN;
	FILE *fp;
	fp=fopen("D:\\MIN\\research\\Plot python\\choatic neuron 24 25.txt","w");
	/*定义变量和初始化*/
	srand(time(0));
   
	
		/*初始化网络矩阵*/
	//for(kr=0;kr<=1;kr+=0.01){
		//for(kf=0;kf<=1;kf+=0.01){

	    feedback=0;refractoriness=0;	
		
		for(int i=0;i<50;i++){
			for(int j=0;j<50;j++){
				Wup[i][j]=0;Wdown[i][j]=0;Wleft[i][j]=0;Wright[i][j]=0;
				if((i>=25&&i<=25)&&(j>=25&&j<=25)){
						x[i][j]=1;
						f[i][j]=1;
						r[i][j]=1;
						ist[i][j]=1;
						y[i][j]=1;
				        }
				else{
						x[i][j]=1;
						f[i][j]=1;
						r[i][j]=1;
				        ist[i][j]=1;
						y[i][j]=1;
					    }
					}
				}

		 for(int step=0;step<=1500;step=step+1){
			 MAX=MIN=0;
			 for(int i = 0;i<50;i++){
				 for(int j = 0;j<50;j++){
					 
					/*权重计算*/
					if(x[(i-1<0)?49:i-1][j] == x[i][j])     Wup[i][j] = 0.5;
 						else                                Wup[i][j] = -0.5;
 					if(x[(i+1)%50][j] == x[i][j])           Wdown[i][j] = 0.5;
 						else                                Wdown[i][j] = -0.5;
 					if(x[i][(j-1<0)?49:j-1] == x[i][j])     Wleft[i][j] = 0.5;
 						else                                Wleft[i][j] = -0.5;
 					if(x[i][(j+1)%50] == x[i][j])           Wright[i][j] = 0.5;
 						else                                Wright[i][j] = -0.5;

						/* if(i == 0)       Wleft = 0;
						 else{ 
 							 if(x[i - 1][j] == x[i][j])   Wleft = -0.25;
 						    else                         Wleft = 0.25;
						    }
						if(i == 49)       Wright = 0;
 						else{ 
 							if(x[i + 1][j] == x[i][j])      Wright = -0.25;
 						    else                            Wright = 0.25;
				          }
				       if(j == 0)        Wup = 0;
 					   else{
 						    if(x[i][j-1] == x[i][j])        Wup = -0.25;
 							else                            Wup = 0.25;
				         }
				       if(j == 49)       Wdown = 0;
 						else{
 						    if(x[i][j+1] == x[i][j])        Wdown = -0.25;
 							else                            Wdown = 0.25;
				        }*/
					if(step>=40){
						if(i==24&&j==25) Wdown[24][25] = 0;
						if(i==26&&j==25) Wup[26][25] = 0;
						if(i==25&&j==24) Wright[25][24] =0;
						if(i==25&&j==26) Wleft[25][26] = 0;
						if(i==25&&j==25){
								Wup[25][25] = 0; Wright[25][25] = 0;Wdown[25][25] = 0; Wleft[25][25] = 0;
							}
					}
					
						WeightSum[i][j]=Wup[i][j]*x[(i-1<0)?49:i-1][j]+Wdown[i][j]*x[(i+1)%50][j]+Wleft[i][j]*x[i][(j-1<0)?49:j-1]+Wright[i][j]*x[i][(j+1)%50];
				
						/*核心计算*/
						feedback=kf*f[i][j]+WeightSum[i][j];
						refractoriness=kr*r[i][j]-l*x[i][j]+o;
						f[i][j]=feedback;
						r[i][j]=refractoriness;	
						if(i==0&&j==0) MAX=MIN=f[0][0];
						if(f[i][j]>MAX) MAX=f[i][j];
						if(f[i][j]<MIN) MIN=f[i][j];

						 }
					 }

            for(int i = 0;i<50;i++){
				 for(int j = 0;j<50;j++){

				         ist[i][j]=f[i][j]+r[i][j];
					     x[i][j]=sigmod(ist[i][j],e);
						 y[i][j]=x[i][j];
					    // if(x[i][j]<0.5)  x[i][j]=0;	
					     //else             x[i][j]=1;
						//printf("%lf\n",(f[i][j]-MIN)/(MAX-MIN));
						 }
					 }
			//printf("%lf %lf\n",MAX,MIN);

			//fprintf(fp,"%lf %lf %lf\n",kr,kf,ist[23][25]);
			
			
			fprintf(fp,"%d %lf %lf %lf %lf\n",step,f[24][25],r[24][25],x[24][25],WeightSum[24][25]);
			
		 }

		 //}
		// }

return 0;
}