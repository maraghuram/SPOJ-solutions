#include <cstdio>
#include <vector>

using namespace std;

vector<vector<int> > tree;
vector<int> parent,level;
vector<vector<int> > P;

void dfs(int node,int depth,int par)
{
	level[node]=depth;	
	
	for(int i=0;i<(int)tree[node].size();++i)
	{
		int v;
		
		v=tree[node][i];
		
		if(v!=par)
		{
			parent[v]=node;			
			dfs(v,depth+1,node);
		}
	}	
}

void init(int N)
{
	int log=0;
	for(;1<<log<=N;++log);
	
	parent=vector<int>(N+1,0);
	level=vector<int>(N+1,0);
	P=vector<vector<int> >(N+1,vector<int>(log,-1));	
	parent[1]=-1;
}


void pre_process(int N)
{		
	for(int i=1;i<=N;++i)
		P[i][0]=parent[i];
	
	
	for(int j=1;1<<j<=N;++j)
		for(int i=1;i<=N;++i)
		{
			if(P[i][j-1]!=-1)
				P[i][j]=P[P[i][j-1]][j-1];
		}
}

int lca(int p,int q)
{
	int temp,log,i;
	
	if(level[p]<level[q])
		temp=p,p=q,q=temp;
	
	for(log=0;1<<log<=level[p];++log);
	--log;
	for(i=log;i>=0;--i)
		if(level[p]-(1<<i)>=level[q])
			p=P[p][i];
	
	if(p==q)
		return p;
	
	for(i=log;i>=0;--i)
		if(P[p][i]!=-1 && P[p][i]!=P[q][i])
			p=P[p][i],q=P[q][i];
	
	return parent[p];
}

int main()
{
	int T;
	
	scanf("%d",&T);
	for(int k=1;k<=T;++k)
	{
	int N;
	
	scanf("%d",&N);
	init(N);
	tree=vector<vector<int> >(N+2,vector<int>(0,0));
	for(int i=1;i<=N;++i)
	{
		int adj;
		scanf("%d",&adj);
		for(int j=1;j<=adj;++j)
		{
			int v;
			scanf("%d",&v);
			tree[i].push_back(v);
			tree[v].push_back(i);	
		}		
	}	
	dfs(1,0,-1);	
	pre_process(N);	
	
	int query;
	scanf("%d",&query);
	printf("Case %d:\n",k);
	for(int i=0;i<query;++i)
	{
		int st,en;
		scanf("%d%d", &st, &en);
		printf("%d\n",lca(st, en));
	}
	
	}
	
	return 0;
}