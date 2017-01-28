#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>

using namespace std;
const int MAX=6101;

static short int cost[MAX][MAX],N;
char input[MAX];

void DoDynamicProgramming()
{
	N=strlen(input);
	memset(cost,0,sizeof(cost));

	for(int i=N-1;i>=0;--i)
		for(int j=i+1;j<N;++j)
		{
			if(input[i]==input[j])
				cost[i][j]=cost[i+1][j-1];
			else
				cost[i][j]=min(cost[i+1][j]+1,cost[i][j-1]+1);
		}
}

int main()
{
	int T;
	scanf("%d",&T);

	while(T>0)
	{
		scanf("%s",input);

		DoDynamicProgramming();

		printf("%d\n",cost[0][N-1]);

		--T;
	}

	return 0;
}
