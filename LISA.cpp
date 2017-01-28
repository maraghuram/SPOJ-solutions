#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>

using namespace std;
const int MAX=105;

typedef long long int x64;

x64 costMax[MAX][MAX],costMin[MAX][MAX],N;
char operations[MAX];
char input[MAX];

void parseInput()
{
	int len=strlen(input);
	N=0;
	costMax[N][N]=costMin[N][N]=input[0]-'0';
	++N;
	for(int i=1;i<len;i+=2)
		operations[N-1]=input[i],costMax[N][N]=costMin[N][N]=input[i+1]-'0',++N;
}

x64 compute(x64 left,x64 right,int i)
{
	if(operations[i]=='+') return left+right;
	else return left*right;
}

void doDynamicProgrammingMax()
{
	for(int len=2;len<=N;++len)
	{
		for(int i=0;i+len-1<N;++i)
		{
			int j=i+len-1;
			costMax[i][j]=LLONG_MIN;
			for(int k=i;k<j;++k)
				costMax[i][j]=max(costMax[i][j],compute(costMax[i][k],costMax[k+1][j],k));
		}
	}
}

void doDynamicProgrammingMin()
{
	for(int len=2;len<=N;++len)
	{
		for(int i=0;i+len-1<N;++i)
		{
			int j=i+len-1;
			costMin[i][j]=LLONG_MAX;
			for(int k=i;k<j;++k)
				costMin[i][j]=min(costMin[i][j],compute(costMin[i][k],costMin[k+1][j],k));
		}
	}
}


int main()
{
	int T;
	scanf("%d",&T);
	while(T>0)
	{
		scanf("%s",input);
		parseInput();

		doDynamicProgrammingMax();
		doDynamicProgrammingMin();

		printf("%lld %lld\n",costMax[0][N-1],costMin[0][N-1]);
		--T;
	}
	return 0;
}
