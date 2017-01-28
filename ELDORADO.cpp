#include <cstdio>

const int MAX=100;

long long int dp[MAX+1][MAX+1],result;
int array[MAX];

void do_dp(int n,int k)
{
	for(int i=0;i<n;++i)
		for(int j=0;j<=k;++j)
			dp[i][j]=0;

	for(int i=0;i<n;++i)
		dp[i][1]=1;

	for(int i=0;i<n;++i)
		for(int j=0;j<i;++j)
			if(array[i]>array[j])
				for(int l=2;l<=k;++l)
					dp[i][l]+=dp[j][l-1];
	result=0;

	for(int i=0;i<n;++i)
		result+=dp[i][k];
}

int main()
{
	int N,K;
	while(scanf("%d %d",&N,&K) && N!=0 && K!=0)
	{
		for(int i=0;i<N;++i)
			scanf("%d",&array[i]);
		do_dp(N,K);
		printf("%lld\n",result);
	}
	return 0;
}
