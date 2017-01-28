#include <cstdio>
#include <climits>
#define MAX 100

int array[MAX],cost[MAX][MAX],color[MAX][MAX];
int N;

void init()
{
	for(int i=0;i<N;++i)
	{
		int sum=array[i];
		color[i][i]=sum;
		for(int j=i+1;j<N;++j)
		{
			sum=(sum+array[j])%MAX;
			color[i][j]=sum;
		}
	}

	for(int i=0;i<N;++i)
		cost[i][i]=0;
}

void compute()
{
	for(int length=2;length<=N;++length)
		for(int i=0;i+length-1<N;++i)
		{
			int j=i+length-1;
			cost[i][j]=INT_MAX;
			for(int k=i;k<j;++k)
			{
				int val=cost[i][k]+cost[k+1][j]+color[i][k]*color[k+1][j];

				if(val<cost[i][j])
				{
					cost[i][j]=val;
					color[i][j]=(color[i][k]+color[k+1][j])%MAX;
				}
			}

		}

}


int main()
{
	while(scanf("%d",&N)==1)
	{

		for(int i=0;i<N;++i)
			scanf("%d",&array[i]);
		init();
		compute();
		printf("%d\n",cost[0][N-1]);
	}

	return 0;
}
