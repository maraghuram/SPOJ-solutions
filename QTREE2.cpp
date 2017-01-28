#include <cstdio>
#include <vector>

using namespace std;

vector<vector<pair<int,int> > > tree;
vector<int> parent,level,nodeCost;
vector<vector<int> > P;

void dfs(int node,int depth,int par)
{
	level[node]=depth;	
	
	for(int i=0;i<(int)tree[node].size();++i)
	{
		int v,cost;
		
		v=tree[node][i].first;
		cost=tree[node][i].second;
		
		if(v!=par)
		{
			parent[v]=node;
			nodeCost[v]=nodeCost[node]+cost;
			dfs(v,depth+1,node);
		}
	}	
}

void init(int N)
{
	int log=0;
	for(;1<<log<=N;++log);
	
	parent=vector<int>(N+1,0);
	nodeCost=vector<int>(N+1,0);
	level=vector<int>(N+1,0);
	P=vector<vector<int> >(N+1,vector<int>(log,-1));	
	parent[1]=-1;
}

void print()
{
	for(int i=1;i<(int)parent.size();++i)
		printf("\n %d %d %d %d ",i,parent[i],nodeCost[i],level[i]);
	
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

int find(int p, int t) {
int i, stp;
for(stp = 1; 1<<stp <= level[p]; stp++); stp--;
for(i = stp; i >= 0; i--)
if(level[p] - (1<<i) >= t)
p = P[p][i];
return p;
}

int main()
{
	int T;
	
	scanf("%d",&T);
	while(T>0)
	{
	int N;
	
	scanf("%d",&N);
	init(N);
	tree=vector<vector<pair<int,int> > >(N+2,vector<pair<int,int> >(0,pair<int,int>(0,0)));
	for(int i=0;i<N-1;++i)
	{
		int u,v,cost;
		scanf("%d %d %d",&u,&v,&cost);
		
		tree[u].push_back(pair<int,int>(v,cost));
		tree[v].push_back(pair<int,int>(u,cost));
	}
	
	dfs(1,0,-1);	
	
	pre_process(N);
	
	char query[6];
	
	while(scanf("%s", query)==1)
	{
		int st,en,u,v,k;
		if(query[1]=='O') break;
		scanf("%d%d", &st, &en);
		u = lca(st, en);
		if(query[1]=='I')
			printf("%d\n", nodeCost[st]+nodeCost[en]-2*nodeCost[u]);
		else if(query[1]=='T')
		{
			scanf("%d", &k);
			if(level[st]-level[u]+1 >= k) v = find(st, level[st]-k+1);
			else v = find(en, 2*level[u]+k-level[st]-1);
			printf("%d\n", v);
		}
	}
	printf("\n");
	--T;
	}
	
	return 0;
}