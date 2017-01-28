#include <bits/stdc++.h>
#define NMAX 11111
#define EMAX 111111
#define KMAX 333
#define x first
#define y second
#define gc getchar_unlocked
#define inf 999999999

using namespace std;
typedef pair<int,int> pii;

void _scan(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

vector<pii> graph[2][NMAX];
int N,M;

inline void addEdge( int u,int v,int cost ){
  graph[0][u].push_back(pii(v,cost));
  graph[1][v].push_back(pii(u,cost));
}

int s,t;
int dist[2][NMAX], visited[NMAX];
int cnt;

void shpath( int u ) {

  for(int i=1;i<=N;++i) visited[i]=0, dist[cnt][i]=inf;

  priority_queue< pii, vector<pii>,  greater<pii> > q;

  q.push(pii(0,u));
  while(!q.empty()){
    pii top = q.top();
    q.pop();

    if( visited[top.y] ) continue;
    
    visited[top.y]=1;
    dist[cnt][top.y]=top.x;
    for(int i=0;i<graph[cnt][top.y].size();++i){
      int v = graph[cnt][top.y][i].x;
      int cost = graph[cnt][top.y][i].y;
      if( !visited[v] )
	q.push(pii(top.x+cost,v));
    }
  }

  ++cnt;
}

int K;
int start[KMAX], end[KMAX], newCost[KMAX];


void readInput(){
  int u,v,c;
  _scan(N);
  _scan(M);
  _scan(K);
  _scan(s);
  _scan(t);
  
  for(int i=1;i<=N;++i ){
    graph[0][i].clear();
    graph[1][i].clear();
  }
  for(int i=0;i<M;++i){
    _scan(u);
    _scan(v);
    _scan(c);
    addEdge(u,v,c);
  }
  for(int i=0;i<K;++i){
    _scan(u);
    _scan(v);
    _scan(c);
    start[i]=u;
    end[i]=v;
    newCost[i]=c;
  }
}

void solve(){

  cnt=0;
  shpath(s);
  shpath(t);

  int minDist = dist[0][t];
  int u,v,cost,left,right;

  for(int i=0;i<K;++i){
    u=start[i],v=end[i],cost=newCost[i];
    left = dist[0][u];
    right = dist[1][v];
    if( left!= inf && right != inf )
      minDist = min( minDist, left+cost+right );
    left = dist[0][v];
    right = dist[1][u];
    if( left!= inf && right != inf )
      minDist = min( minDist, left+cost+right );
  }

  if( minDist != inf ) printf("%d\n",minDist);
  else printf("-1\n");

}

int main(){
  int T;
  _scan(T);

  while(T--){
    readInput();
    solve();
  }

  return 0;
}
