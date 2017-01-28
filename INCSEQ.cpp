#include <cstdio>
#include <algorithm>

using namespace std;

const int MOD=5000000,N=10005,K=53,MAX=100005;

int LIM;
int f[K][N],seq[N],temp[N],map[MAX];

void update(int *B,int idx,int val)
{
	for(;idx<LIM;idx+=(idx & -idx))
		if((B[idx]+=val)>=MOD) B[idx]-=MOD;
}

int read(int *B,int idx)
{
	int res=0;

	for(;idx>0;idx-=(idx & -idx))
		if((res+=B[idx])>=MOD) res-=MOD;

	return res;
}

int main()
{
	int n,k;

	scanf("%d %d",&n,&k);
	for(int i=0;i<n;++i) scanf("%d",&seq[i]),temp[i]=seq[i];

	sort(seq,seq+n);

	LIM=0;
	map[seq[0]]=++LIM;

	for(int i=1;i<n;++i)
		if(seq[i-1]!=seq[i]) map[seq[i]]=++LIM;

	++LIM;

	for(int i=0;i<n;++i)
	{
		int val=map[temp[i]];
		update(f[1],val,1);

		for(int l=2;l<=k;++l)
		{
			int t=read(f[l-1],val-1);
			if(t) update(f[l],val,t);
		}
	}


	printf("%d\n",read(f[k],LIM-1));

	/*for(int i=1;i<=k;++i)
	{
		printf("\n %d - ",i);
		for(int j=1;j<LIM;++j)
			printf(" %d",f[i][j]);
	}
*/


	return 0;
}
