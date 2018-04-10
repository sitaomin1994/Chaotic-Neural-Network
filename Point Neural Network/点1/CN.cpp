# include <windows.h>    // Windows的头文件
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <GL/glut.h>
# define PI 3.1415926
#define MAX_CHAR 128


double a[300][300];
double b[300][300];
double c[300][300];
int count=1;
int count2=0;
double	kr=0.6;
double l=10.0,o=2.0,e=0.015,kf=0.0;								//kr 不应性系数 
double f(double z,double e){
	double result;
	result=1.0/(1.0+exp(-z/e));
	return result;	
}
void init(){
  glClearColor (1.0f, 1.0f, 1.0f, 0.0);
  glMatrixMode (GL_PROJECTION);
  gluOrtho2D (-10.0, 1300.0, -10.0, 700.0);
}
void display(void){
	double feedback=0,refractoriness=0;							//feedback 反馈项 refractoriness 不应性项
	double Wup=0,Wdown=0,Wleft=0,Wright=0;                      //Wup,Wdown,Wleft,Wright为每个神经元相邻神经元之间的连接权重 
	int k=0;					
	double ist,sum=0;                                           //ist:内部状态函数  t:时间  kf反馈系数 
	FILE *fp1;
	fp1=fopen("choatic neuron.txt","w");
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	kf=0.9;
	/*40step的迭代过程*/

	/*计算并输出每个矩形Start*/ 
		/*神经元迭代计算过程*/ 
 		for(int i=0;i<300;i++){
 			for(int j=0;j<300;j++){
 				/*连接权重的计算*/
 			/*连接权重的计算*/
 				if(a[(i-1<0)?49:i-1][j]==a[i][j]) Wleft= 0.25;
 				else Wleft= -0.25;
 				if(a[(i+1)%50][j]==a[i][j]) Wright= 0.25;
 				else Wright= -0.25;
 				if(a[i][(j-1<0)?49:j-1]==a[i][j]) Wup= 0.25;
 				else Wup= -0.25;
 				if(a[i][(j+1)%50]==a[i][j]) Wdown= 0.25;
 				else Wdown= -0.25;

				sum=Wleft*a[(i-1<0)?49:i-1][j]+Wright*a[(i+1)%50][j]+Wup*a[i][(j-1<0)?49:j-1]+Wdown*a[i][(j+1)%50];
	        
	        
				/*迭代过程*/    
				feedback=kf*b[i][j]+sum;
				refractoriness=kr*c[i][j]-l*a[i][j]+o;
				b[i][j]=feedback;
				c[i][j]=refractoriness;	
				 }
 			}
		/*外部输出*/
		for(int i=0;i<300;i++){
			for(int j=0;j<300;j++){
				ist=b[i][j]+c[i][j];
				a[i][j]=f(ist,e);
					/*输出*/
				if(a[i][j]<0.5&&a[i][j]>=0) 
					a[i][j]=0;	
				else 
					a[i][j]=1;
			}
		}

		/*显示输出*/
		for(int i=0;i<300;i++){
			for(int j=0;j<300;j++){
				if(a[i][j]==1.0){
					glColor3f(0.0f, 0.0f, 0.0f);
					glVertex2i(2*(i)+350, 2*(j)+50);
					}
				else{
					glColor3f(1.0f, 0.95f, 1.0f);
					glVertex2i(2*(i)+350, 2*(j)+50);
				}
			}
		}
	 glColor3f(1.0f, 0.0f, 0.0f);
	 for(int i=0;i<count;i++)
		 glVertex2i(3*(i), -5);
	 for(int i=0;i<count2;i++)
		 glVertex2i(3*(i),-8);
	glEnd();
	glFlush();
	glutSwapBuffers();
}
void MouseClick(int button, int state, int x, int y)  
{ 
	
	if(state==GLUT_DOWN)
    {
        if(button==GLUT_LEFT_BUTTON)
        {   count=0;
			count2++;
			kr=kr+0.05;
				for(int i=0;i<300;i++){
					for(int j=0;j<300;j++){
					//if((i>=15&&i<=34)&&(j>=15&&j<=34)/*||(j==15&&i==34)||(j==34&&i==34)*/){
					if((i>=150&&i<=151)&&(j>=150&&j<=151)/*||(j==15&&i==34)||(j==34&&i==34)*/){
						a[i][j]=0;//rand()%2;
						b[i][j]=0;//rand()%2;
						c[i][j]=0;//rand()%2;
					}
					
				   else{
						a[i][j]=1;//rand()%2;
						b[i][j]=1;//rand()%2;
						c[i][j]=1;//rand()%2;
				   
					  }
					}
				}
					
            glutPostRedisplay();
		}   
    }
   
}
void timer(int value){
  glutPostRedisplay();
  count++;
  glutTimerFunc(500, timer, 1);

}
int main(int argc, char *argv[])
{
/*定义变量和初始化*/
	srand(time(0));
    /*初始化网络矩阵*/
	for(int i=0;i<300;i++){
		for(int j=0;j<300;j++){
			//if((i>=15&&i<=34)&&(j>=15&&j<=34)/*||(j==15&&i==34)||(j==34&&i==34)*/){
			if((i>=150&&i<=151)&&(j>=150&&j<=151)){
						a[i][j]=0;//rand()%2;
						b[i][j]=0;//rand()%2;
						c[i][j]=0;//rand()%2;
				}
			else{
						a[i][j]=1;//rand()%2;
						b[i][j]=1;//rand()%2;
						c[i][j]=1;//rand()%2;
				   
					  }
					}
				}
 
/*调用OpenGL图形窗口*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1310, 710);
	glutCreateWindow("choatic network");
 
	init();
	glutDisplayFunc(&display);
	//glutPostRedisplay();
	glutTimerFunc(10, timer, 1);
	glutMouseFunc(MouseClick);  
	glutMainLoop();
	

return 0;
}