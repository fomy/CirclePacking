#include "stdafx.h"
#include "Packing.h"
//#include "CirclePackingView.h"

//void (*ShowPattern)(Pattern pattern);
extern void DrawPattern(Pattern pattern);

int PackingMain(int argc, char **argv)//输入半径
{
	/******处理输入参*******/
	if(argc<2)
	{	
		return 0;
	}
	char *msg=*argv;
	char *buf=(char*)malloc(100);
	ser_declare;
	ser_begin(msg);
	unser_string(buf);
	double rate=atof(buf);
	unser_string(buf);
	int N=atoi(buf);
	double *radius=(double*)malloc(N*sizeof(double));
	for(int i=0;i<N;++i)
	{
		unser_string(buf);
		*(radius+i) = atof(buf);/*将字符串转化为double*/
	}
	/*****产生随机坐标*****/
	srand(time(NULL));
	double *seat=(double*)malloc(2*N*sizeof(double));
	for(int i=0; i<2*N; i++)
	{
		seat[i]=2*((double)(rand()%89)+1)/97;
	}
	/*******初始化格局***/
	Pattern *pattern=(Pattern *)malloc(sizeof(Pattern));
	pattern->container=InitCircle(1,1,1);
	pattern->N=N;
	pattern->h=INITH;
	pattern->t=INITT;
	pattern->energy=100;
	pattern->flag=0;

	pattern->circles=(Circle**)malloc(N*sizeof(Circle*));
	for(int i=0;i<N;++i)
	{
		pattern->circles[i]=InitCircle(seat[i], seat[i+1], radius[i]/rate);
	}
	
	/*释放radius和seat*/
	free(radius);
	free(seat);
	radius=0;
	seat=0;

	int count=1;
	DrawPattern(*pattern);
	Circle *pity =0;
	Circle *old_pity =0;
	while(pattern->energy>D)//这是误差
	{
		Update(pattern);//这是上一状态的能量和方向
		//if(pattern->h/pattern->energy<0.000001)//存在问题，在最优解附近可能跳出去
		if(pattern->h<MINH)
		//if(count>100)
		//if(pattern->flag>0 && pattern->h < pattern->energy)//大于就跳
		{
			pity = pattern->circles[0];
			for(int i=1;i<N;++i)
				pity = pity->eng/square(pity->radius) > pattern->circles[i]->eng/square(pattern->circles[i]->radius) ? pity : pattern->circles[i];
			if(pity==old_pity)
			{
				pity = pattern->circles[0];
				for(int i=1;i<N;++i)
					pity = pity->eng < pattern->circles[i]->eng ? pity : pattern->circles[i];
			}
			old_pity=pity;
			/*完全随机
			pity->x=2*((double)(rand()%89)+1)/97;
			pity->y=2*((double)(rand()%89)+1)/97;
			*/
			/*固定四个点，取最远点
			if(pity->x-1>0)
				pity->x=0;
			else
				pity->x=2;
			if(pity->y-1>0)
				pity->y=0;
			else
				pity->y=2;
			*/
			/*固定五个点，随机取一个*/
			int i  = rand()%5;
			switch(i){
				case 0:
					pity->x=0;
					pity->y=0;
					break;
				case 1:
					pity->x=2;
					pity->y=0;
					break;
				case 2:
					pity->x=0;
					pity->y=2;
					break;
				case 3:
					pity->x=2;
					pity->y=2;
					break;
				case 4:
					pity->x=1;
					pity->y=1;
					break;
			}
			Update(pattern);
			pattern->flag=0;
			DrawPattern(*pattern);
			pattern->h=0.2;
			//count=0;
		}
		else if(pattern->flag<0)// && pattern->h>MINH)
	//	else if(pattern->flag<0&& pattern->h>MINH)//势能上升了
			pattern->h=pattern->t*pattern->h;//梯度下降
		//else if( pattern->h<=MINH)
		{
			//count++;
			/*
			if(count>100)
			{
				for(int i=0;i<N;i++)
					free(pattern->circles[i]);
				free(pattern->circles);
				free(pattern->container);
				free(pattern);
				return -1;
			}
			*/
		}
		/*计算并移动到下一个格局*/
		double h = pattern->h;
		for(int i=0; i<N; ++i)
		{
			Circle *p = pattern->circles[i];
			double x=p->direct.x;
			double y=p->direct.y;
			if(x!=0 || y!=0)
			{
				p->x+=x*sqrt(h*h/(x*x+y*y));
				p->y+=y*sqrt(h*h/(x*x+y*y));
			}
		}
		DrawPattern(*pattern);
	}

	/*释放内存*/
	for(int i=0;i<N;i++)
		free(pattern->circles[i]);
	free(pattern->circles);
	free(pattern->container);
	free(pattern);
	return 0;
}

Circle *InitCircle(double x, double y, double r)
{
	Circle *pCircle=(Circle *)malloc(sizeof(Circle));
	pCircle->x=x;
	pCircle->y=y;
	pCircle->radius=r;
	return pCircle;
}

double Range(Circle c1, Circle c2)
{
	double dist=0;
	if(c1.x==1 && c1.y==1)
	{
		//与容器的距离
		double d=distance(1,1,c2.x,c2.y) ;
		dist=1 - (d+ c2.radius);
	}
	else if(c2.x==1 && c2.y==1)
	{
		//与容器的距离
		dist=1 - (distance(c1.x,c1.y,1,1) + c1.radius);
	}
	else
	{
		dist=distance(c1.x,c1.y,c2.x,c2.y) - (c1.radius+c2.radius);
	}
	return dist;
}

double Energy(Circle c1, Circle c2)
{
	double energy=0;
	double range=Range(c1, c2);
	if(range>=0)
	{
		energy=0;
	}
	else
	{
		energy=square(range);
	}
	return energy;
}

/*根据坐标计算当前的势能和各个球运动的方向*/
void Update(Pattern *pattern)
{
	int N=pattern->N;
	double oldEng=pattern->energy;
	pattern->energy=0;
	for(int i=0;i<N;i++)
	{
		Circle *c1=pattern->circles[i];
		c1->direct.x=0;
		c1->direct.y=0;
		c1->eng=0;
	}

	for(int n=0; n<N;++n)
	{
		Circle *c1=pattern->circles[n];
		/*更新与容器的势能和作用力方向*/
		/*用对角线保存与容器的势能*/
		double e0=Energy(*(pattern->container),*c1);
		c1->direct.x+= (pattern->container->x - c1->x)*e0;
		c1->direct.y+= (pattern->container->y - c1->y)*e0;
		c1->eng+=e0;
		pattern->energy+=e0;
		/**********更新与其他结点的关系*************/
		for(int m=n+1;m<N;++m)
		{
			Circle *c2=pattern->circles[m];
			double e1=Energy(*c1,*c2);
			c1->direct.x+=(c1->x - c2->x)*e1;
			c1->direct.y+=(c1->y - c2->y)*e1;
			c2->direct.x+=(c2->x - c1->x)*e1;
			c2->direct.y+=(c2->y - c1->y)*e1;
			c1->eng+=e1;
			c2->eng+=e1;
			pattern->energy+=e1;
		}
	}
	pattern->flag=oldEng - pattern->energy;
}

void serial_string(char * * const ptr, const char * const str)
{
   int len = strlen(str) + 1;
   memcpy(*ptr, str, len);
   *ptr += len;
}

void unserial_string(char * * const ptr, char * const str)
{
   int len = strlen((char *) *ptr) + 1;
   memcpy(str, (char *) *ptr, len);
   *ptr += len;
}