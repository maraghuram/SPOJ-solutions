#include <bits/stdc++.h>
#define NMAX 555555

using namespace std;
typedef long long int ll;

int from[NMAX<<1],to[NMAX<<1],next[NMAX<<1];
ll cost[NMAX<<1];
int cnt;

inline void addEdge( int u,int v,ll w ){
	to[cnt]=v;
	next[cnt]=from[u];
	from[u]=cnt;
	cost[cnt++]=w;
}

int mxNode;
ll mxDist;

void dfs(int u,int p,ll d){
	//cout<<u<<" "<<p<<" "<<d<<endl;
	if(d>mxDist) mxNode=u,mxDist=d;
	for(int i=from[u];i;i=next[i]){
		int v=to[i];
		//cout<<v<<endl;
		ll cst=cost[i];
		if( v!=p ) dfs(v,u,d+cst);
	}
}

int main(){

	int t;
	cin>>t;
	for(int i=0;i<t;++i){
		memset(from,0,sizeof(from));
		memset(to,0,sizeof(to));
		memset(next,0,sizeof(next));
		memset(cost,0,sizeof(cost));
		int n;
		cin>>n;
		cnt=1;
		for(int j=0;j<n-1;++j){
			int u,v;
			ll w;
			cin>>u>>v>>w;
			addEdge(u,v,w);
			addEdge(v,u,w);
		}
		mxNode=mxDist=-1;
		dfs(1,-1,0);
		assert(mxNode);

		dfs(mxNode,-1,0);
		assert(mxNode);
		cout<<mxDist<<endl;
	}

	return 0;
}
