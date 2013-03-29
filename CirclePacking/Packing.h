#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/*����*/
#define PIE 3.1415926
#define MULTI (250) /*�Ŵ���*/
#define CENTREX (100)/*Բ��ƫ��*/
#define CENTREY (40)
#define D (0.000001) //��������
#define MINH (0.0001) //h����Сֵ
#define INITH (0.2)
#define INITT (0.7)
/*��ѧ�����*/
#define square(x) ((x)*(x))
#define area(c) (PIE*(c).radius*(c).radius)
#define distance(x1, y1, x2, y2) sqrt((square((x1)-(x2))+square((y1)-(y2))))
/*�ַ�������*/
#define ser_begin(x) ser_ptr = ((char *)(x))
#define ser_declare     char *ser_ptr
#define ser_string(x)   serial_string(&ser_ptr, (x))//���л�
#define unser_string(x) unserial_string(&ser_ptr, (x))//�����л�

typedef struct Direct
{
	double x;
	double y;
}Direct;

typedef struct Circle
{
	//����
	double x;
	double y;
	double radius;
	Direct direct;
	double eng;//�������
}Circle;

typedef struct Pattern
{
	int N;//�������
	double h;//�ƶ��ٶ�
	double t;//�ݶ�
	double energy;//������
	Circle **circles;//N circles
	Circle *container;//container
	double flag;//��־���ܷ����ı仯��<0�����,0�����䣩,>0����С��
}Pattern;



int PackingMain(int argc, char **argv);
Circle *InitCircle(double x, double y,double r);
double Range(Circle c1, Circle c2);
double Energy(Circle c1, Circle c2);
void Update(Pattern *pattern);
void serial_string(char * * const ptr, const char * const str);
void unserial_string(char * * const ptr, char * const str);