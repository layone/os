#include<stdio.h>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#define N 128   //虚拟内存大小
#define MAX 2000    //引用串的长度
#define P 32  //物理内存大小

using namespace std;
int result;  //置换次数
int RS[100] = {};  //RS串
int M[P] = {0};   // 物理内存大小

void PRS()
{
	int p = 1;//工作集的起始位置p
	int e = 40;//工作集中包含的页数e
	int m = 64;//工作集移动率m
	double t = 0.5;
	int judge = 1;
	int count = 0;
	double r;
	while(judge == 1)
	{
		srand((unsigned)time(NULL));
		for(int i = 0;i < m;i++)
		{
			RS[count] = rand()%e+p;
			count++;
		}
		r = (rand()%9+1)/10;
		if(r < t)
		{
			p = rand()%N+1;
		}
		else
		{
			p = (p+1)%N;
		}
		if(count >= MAX){
            printf("以下是生成的引用串:\n");
            for(int i = 0;i < count;i++)
            {
                printf("%d ",RS[i]);
            }
            printf("\n");
            break;
		}
	}
}

void print(int c)
{
	printf("以下为物理内存情况：\n");
	for(int i = 0;i < c;i++)
	{
		printf("%d ",M[i]);
	}
	printf("\nend**********************\n");
}

//判断物理内存是否已满
int full(int c,int j)
{
	int judge = 0;
	for(int i = 0;i < c;i++)
	{
		if(RS[j] == M[i])
		{
			judge = 1;
			break;
		}
	}
	if(!judge)
	{
		M[c] = RS[j];
		c++;
	}
	return c;
}

//判断是否为缺页
int lack(int c, int j)
{
	int judge = 0;
	for(int i = 0;i < c;i++)
	{
		if(RS[j] == M[i])
		{
			judge = 1;
			break;
		}
	}
	return judge;
}


//最佳置换算法
int OPT()
{
	result = 0;
	int count = 0;
	for(int j = 0;j < MAX;j++)
	{
		int judge = 0;
		if(count < P)
		{
			count = full(count,j);
		}
		else
		{
			int number;
			judge = lack(count,j);
			if(!judge)   //没有找到，需进行置换
			{
				result++;
				int s;  //用于存放没有找到的页面的数组下标
				for(int k = 0;k < count;k++)
				{
					number = -1;
					for(int i = j+1;i < MAX;i++)
					{
						if(M[k] == RS[i])
						{
							if(number < i)
							{
								number = i;
								s = k;
							}
							break;
						}
					}
					//没有找到，说明此页面不会再被使用，所以直接进行替换
					if(number == -1)
					{
						s = k;
						break;
					}
				}
				M[s] = RS[j];
			}
		}
	}
	return result;
}

//先进先出置换算法
int FIFO()
{
	result = 0;
	int p = 0;
	int count = 0;
	for(int j = 0;j < MAX;j++)
	{
		int judge = 0;
		if(count < P)
		{
			count = full(count,j);
		}
		else
		{
			//判断是否是缺页
			judge = lack(count,j);
			//是缺页，进行置换
			if(!judge)
			{
				result++;
				M[p] = RS[j];
				p = (p+1)%P;
			}
		}
	}
	return result;
}

//最近最久未使用置换算法
int LRU()
{
	result = 0;
	int a[P];  //辅组数组,队尾为最近访问页面
	int count = 0;
	for(int j = 0;j < MAX;j++)
	{
		int judge = 0;
		if(count < P)
		{
			for(int i = 0;i < count;i++)
			{
				if(RS[j] == M[i])
				{
					judge = 1;
					//将页面提到队尾
					int change = M[i];
					for(int k = i;k < count-1;k++)
					{
						a[k] = a[k+1];
					}
					a[count-1] = change;

					break;
				}
			}
			if(!judge)
			{
				a[count] = RS[j];
				M[count] = RS[j];
				count++;
			}
		}
		else
		{
			//判断是否是缺页
			for(int i = 0;i < count;i++)
			{
				if(RS[j] == M[i])
				{
					judge = 1;
					//将页面提到队首
					int change = M[i];
					for(int k = i;k < P-1;k++)
					{
						a[k] = a[k+1];
					}
					a[P-1] = change;

					break;
				}
			}
			//是缺页，进行置换
			if(!judge)
			{
				result++;
				for(int i = 0;i < P;i++)
				{
					if(a[0] == M[i])
					{
						M[i] = RS[j];
						for(int k = 0;k < P-1;k++)
						{
							a[k] = a[k+1];
						}
						a[P-1] = RS[j];

						break;
					}
				}
			}
		}
	}
	return result;
}

//Clock置换算法
int CLO()
{
	result = 0;
	int p = 0;
	int a[MAX];   //辅助数组
	int count = 0;
	for(int j = 0;j < MAX;j++)
	{
		int judge = 0;
		if(count < P)
		{
			for(int i = 0;i < count;i++)
			{
				if(M[i] == RS[j])
				{
					a[i] == 1;
					judge = 1;
					break;
				}
			}
			if(!judge)
			{
				a[count] = 1;
				M[count] = RS[j];
				count ++;
			}
		}
		else
		{
			for(int i = 0;i < count;i++)
			{
				if(M[i] == RS[j])
				{
					judge = 1;
					a[i] = 1;
					break;
				}
			}
			//是缺页，进行置换
			if(!judge)
			{
				result++;
				while(1)
				{
					if(a[p] == 1)
					{
						a[p] = 0;
						p = (p+1)%P;
					}
					else
					{
						a[p] = 1;
						M[p] = RS[j];
						p = (p+1)%P;
						break;
					}
				}
			}
		}
	}
	return result;
}

int main()
{
	int condition = 1;
	while(condition)
	{
		//先调用函数生成引用串
		PRS();

		//对于生成的引用串用各个算法进行效率的测试
		char a[4][30] = {"最佳置换算法","先进先出置换算法",\
					     "最近最久未使用置换算法","Clock置换算法"};
		int r[5];
		r[0] = OPT();
		r[1] = FIFO();
		r[2] = LRU();
		r[3] = CLO();
		printf("\n****************************\n");
		printf("最终结果:\n");
		for(int i = 0;i < 4;i++)
		{
		    double q=(float)r[i]/MAX;
			printf("%s置换次数:%d,缺页率：%.3f\n",a[i],r[i],q);
		}
		printf("1.继续;\n");
		printf("0.退出;\n");
		scanf("%d",&condition);
	}
	return 0;
}
