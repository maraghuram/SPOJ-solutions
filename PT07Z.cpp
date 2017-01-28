#include <bits/stdc++.h>
#define NMAX 11111

using namespace std;
typedef pair<int,int> pii;
int N;
int far,val;

vector<int> adj[NMAX];
void addEdge(int u,int v){
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void dfs(int u,int p,int d){
	if(d>val) far=u,val=d;
	for(int i=0;i<adj[u].size();++i){
		int v=adj[u][i];
		if(v!=p) dfs(v,u,d+1);
	}
}

int main(){
  scanf("%d",&N);
  assert(N<=10000);
  for(int i=0;i<N-1;++i) {
    int u,v;
    scanf("%d %d",&u,&v);
    addEdge(u,v);
  }

  dfs(1,-1,0);
  int node=far;
  dfs(node,-1,0);
  printf("%d\n",val);

  return 0;
}


