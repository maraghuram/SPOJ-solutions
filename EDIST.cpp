#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>

using namespace std;

const int MAX=2005;

int cost[MAX][MAX],m,n;
char str1[MAX],str2[MAX];

void doDynamicProgramming()
{
	m=strlen(str1)+1;
	n=strlen(str2)+1;

	for(int j=0;j<n;++j) cost[0][j]=j;

	for(int i=1;i<m;++i)
	{
		cost[i][0]=i;
		for(int j=1;j<n;++j)
			cost[i][j]=min(cost[i-1][j]+1,min(cost[i][j-1]+1,str1[i-1]==str2[j-1]?cost[i-1][j-1]:cost[i-1][j-1]+1));

	}

}

int main()
{
	int T;
	scanf("%d",&T);
	while(T>0)
	{
		scanf("%s",str1);
		scanf("%s",str2);

		doDynamicProgramming();

		printf("%d\n",cost[m-1][n-1]);

		--T;
	}


	return 0;
}
