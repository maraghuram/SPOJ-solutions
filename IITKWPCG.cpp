#include <bits/stdc++.h>
#define NMAX 111111

using namespace std;
typedef pair<int,int> pii;
vector<pii> adj[NMAX];
int visited[NMAX];

inline int _log2( long long int x ){
  return 63 - __builtin_clzll (x);
}


int primsMST( int u ){
  priority_queue< pii, vector<pii>, greater<pii> > q;
  int finalCost = 0;

  q.push(pii(0,u));
  while(!q.empty()){
    pii t = q.top();
    int node = t.second;    
    q.pop();    

    if( visited[node] ) continue;

    finalCost += t.first;
    visited[node]=1;    
    for(int i=0;i<adj[node].size();++i){
      int v = adj[node][i].second;
      int c = adj[node][i].first;
      if( ! visited[v] ) q.push( pii(c,v) );
    }
  }
  return finalCost;
}

int main(){
  int T;
  scanf("%d",&T);
  while(T--){
    int N,M;
    scanf("%d %d",&N,&M);
    for(int i=1;i<=N;++i){
      adj[i].clear();
      visited[i]=0;
    }
    for(int i=0;i<M;++i) {
      int a,b,cost;
      long long int c;
      scanf("%d %d %lld",&a,&b,&c);

      cost = _log2( c );
      adj[a].push_back( pii(cost,b) );
      adj[b].push_back( pii(cost,a) );
    }
    int res = primsMST( 1 ); 
    printf( "%d\n", res + 1 );
  }
  return 0;
}
