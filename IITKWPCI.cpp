#include <bits/stdc++.h>
#define NMAX 1111

using namespace std;

int N,M;
int cnt;
vector<int> adj[NMAX];
vector<int> component[NMAX];
vector<int> componentPos[NMAX];
int visited[NMAX];

int A[NMAX];
int result[NMAX];

void dfs(int u){
  visited[u] = 1;
  componentPos[cnt].push_back(u);
  component[cnt].push_back(A[u]);
  for(int i=0;i<adj[u].size();++i){
    int v = adj[u][i];
    if( !visited[v] ) dfs(v);
  }
}

int main(){
  int T;
  scanf("%d",&T);
  while(T--){
    scanf("%d %d",&N,&M);
    for(int i=0;i<N;++i){
      adj[i].clear();
      visited[i]=0;
    }
    for(int i=0;i<N;++i) scanf("%d",&A[i]);
    for(int i=0;i<M;++i){
      int u,v;
      scanf("%d %d",&u,&v);
      --u,--v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    cnt=0;
    for(int i=0;i<N;++i){
      if( ! visited[i] ){
	++cnt;
	dfs(i);
      }
    }

    for(int i=0;i<=cnt;++i){
      sort(component[i].begin(),component[i].end());
      sort(componentPos[i].begin(),componentPos[i].end());
      for(int j=0;j<component[i].size();++j)
	result[componentPos[i][j]]=component[i][j];
      component[i].clear();
      componentPos[i].clear();
    }
    for(int i=0;i<N-1;++i){
      printf("%d ",result[i]);
    }
    printf("%d\n",result[N-1]);
  }
  return 0;
}
