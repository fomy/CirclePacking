#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/*常量*/
#define PIE 3.1415926
#define MULTI (250) /*放大倍数*/
#define CENTREX (100)/*圆心偏移*/
#define CENTREY (40)
#define D (0.000001) //允许的误差
#define MINH (0.0001) //h的最小值
#define INITH (0.2)
#define INITT (0.7)
/*数学计算宏*/
#define square(x) ((x)*(x))
#define area(c) (PIE*(c).radius*(c).radius)
#define distance(x1, y1, x2, y2) sqrt((square((x1)-(x2))+square((y1)-(y2))))
/*字符串处理*/
#define ser_begin(x) ser_ptr = ((char *)(x))
#define ser_declare     char *ser_ptr
#define ser_string(x)   serial_string(&ser_ptr, (x))//串行化
#define unser_string(x) unserial_string(&ser_ptr, (x))//反串行化

typedef struct Direct
{
	double x;
	double y;
}Direct;

typedef struct Circle
{
	//坐标
	double x;
	double y;
	double radius;
	Direct direct;
	double eng;//球的势能
}Circle;

typedef struct Pattern
{
	int N;//物体个数
	double h;//移动速度
	double t;//梯度
	double energy;//总势能
	Circle **circles;//N circles
	Circle *container;//container
	double flag;//标志势能发生的变化，<0（变大）,0（不变）,>0（变小）
}Pattern;



int PackingMain(int argc, char **argv);
Circle *InitCircle(double x, double y,double r);
double Range(Circle c1, Circle c2);
double Energy(Circle c1, Circle c2);
void Update(Pattern *pattern);
void serial_string(char * * const ptr, const char * const str);
void unserial_string(char * * const ptr, char * const str);