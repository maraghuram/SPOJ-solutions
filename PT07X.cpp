#include <cstdio>
#include <cstring>
#include <vector>
#include <climits>

const int MAXN=100000;

using namespace std;

vector<int> tree[MAXN+5];
int dp[MAXN+5][2];

int solve(int u,int par,bool state)
{
	if(dp[u][state]!=-1) return dp[u][state];

	int result=INT_MAX;

	if(state)
	{
		int res1=1;
		for(int i=0;i<tree[u].size();++i)
		{
			int adj=tree[u][i];
			if(adj!=par) res1+=solve(adj,u,true);
		}
		result=min(result,res1);

		res1=0;
		for(int i=0;i<tree[u].size();++i)
		{
			int adj=tree[u][i];
			if(adj!=par) res1+=solve(adj,u,false);
		}
		result=min(result,res1);
	}
	else
	{
		int res2=1;
		for(int i=0;i<tree[u].size();++i)
		{
			int adj=tree[u][i];
			if(adj!=par) res2+=solve(adj,u,true);
		}
		result=res2;
	}

	dp[u][state]=result;
	return result;
}

int main()
{
	int N,res1,res2;
	scanf("%d",&N);
	for(int i=0;i<N-1;++i)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	memset(dp,-1,sizeof(dp));

	res1=1;
	for(int i=0;i<tree[1].size();++i)
	{
		int adj=tree[1][i];
		if(adj!=1) res1+=solve(adj,1,true);
	}

	res2=0;
	for(int i=0;i<tree[1].size();++i)
	{
		int adj=tree[1][i];
		if(adj!=1) res2+=solve(adj,1,false);
	}

	printf("%d\n",min(res1,res2));

	return 0;
}
