#include <bits/stdc++.h>
#define NMAX 111111
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)

using namespace std;

int N,M;
vector<int> adj[NMAX];
int subtree[NMAX],color[NMAX],depth[NMAX],parent[NMAX];

int dfs(int u,int p,int h){
  subtree[u]=1;
  depth[u]=h;
  parent[u]=p;

  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];
    if(v!=p) subtree[u]+=dfs(v,u,h+1);
  }
  return subtree[u];
}

int chainCnt;
vector<int> chain[NMAX];
int chainId[NMAX],chainPos[NMAX],chainHead[NMAX];

void hld(int u,int p){
  if(chain[chainCnt].size()==0) chainHead[chainCnt]=u;
  chainId[u]=chainCnt;
  chain[chainCnt].push_back(u);
  chainPos[u]=chain[chainCnt].size();

  int most,ind;
  most=ind=-1;

  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];
    if(v!=p && subtree[v]>most) most=subtree[v],ind=v;
  }

  if(ind!=-1) hld(ind,u);

  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];
    if( v!=p && v!=ind ){
      ++chainCnt;
      hld(v,u);
    }
  }

}

struct node{
  node *l,*r;
  int cnt;
  node(){
    l=r=NULL;
    cnt=0;
  }
  node(node *x){
    l=x->l;
    r=x->r;
    cnt=x->cnt;
  }
};

vector<node*> version;
int ver[NMAX];
int cnt;

node* build(int i,int j){
  node *tmp=new node();
  if(i==j) return tmp;
  int mid=(i+j)>>1;
  tmp->l=build(i,mid);
  tmp->r=build(mid+1,j);
  return tmp;
}

void _remove(node *curr){
  if(curr->l) _remove(curr->l);
  if(curr->r) _remove(curr->r);
  delete curr;
}

void _removeAll(){
  for(int i=0;i<version.size();++i){
    //_remove(version[i]);
  }
  version.clear();
}

int pos;

node* update(node *index,int i,int j){
  node *tmp=new node(index);
  if(i==j && i==pos){
    tmp->cnt += 1;
    return tmp;
  }

  int mid=(i+j)>>1;
  if(pos<=mid) tmp->l=update(index->l,i,mid);
  else tmp->r=update(index->r,mid+1,j);
  return tmp;
}

int query(node *ver1,node *ver2,int i,int j,int pos){
  if(i==j && i==pos) return ver2->cnt-ver1->cnt;
  int mid=(i+j)>>1;
  if(pos<=mid) return query(ver1->l,ver2->l,i,mid,pos);
  else return query(ver1->r,ver2->r,mid+1,j,pos);
}

void init(){
  node *tmp = build(0,N);
  cnt=1;
  version.push_back(tmp);
  for(int i=0;i<=chainCnt;++i){
    for(int j=0;j<chain[i].size();++j){
      ver[chain[i][j]]=cnt;
      pos=color[chain[i][j]];
      version.push_back(update(version[cnt-1],0,N));
      ++cnt;
    }
    chain[i].clear();
  }
}


int ask(int u,int v,int w){
  int cu,cv;
  while( chainId[u] != chainId[v] ){    
    cu = chainHead[chainId[u]]; cv = chainHead[chainId[v]];
    if( depth[parent[cu]] < depth[parent[cv]] ){
      //cout << ver[cv]-1 << " " << ver[v] << endl;
      int res = query(version[ver[cv]-1],version[ver[v]],0,N,w);
      if( res>0 ) return 1;
      v = parent[cv];
    }
    else{
      //cout << ver[cu]-1 << " " << ver[u] << endl;
      int res = query(version[ver[cu]-1],version[ver[u]],0,N,w);
      if( res>0 ) return 1;
      u = parent[cu];
    }
  }

  if( depth[u] < depth[v] ){
    int res = query(version[ver[u]-1],version[ver[v]],0,N,w);
    if( res>0 ) return 1;
  }
  else{
    if( query(version[ver[v]-1],version[ver[u]],0,N,w) > 0 ) 
      return 1;
  }

  return 0;
}

int main(){
  while( scanf("%d %d",&N,&M)!=EOF ){
    for(int i=0;i<N;++i) scanf("%d",&color[i+1]);
    for(int i=0;i<N-1;++i){
      int u,v;
      scanf("%d %d",&u,&v);
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
   
    dfs(1,0,1);
    chainCnt=0;
    hld(1,0);
    init();
   
    for(int i=0;i<M;++i){
      int a,b,c;
      scanf("%d %d %d",&a,&b,&c);
      if(ask(a,b,c))
    	printf("Find\n");
      else
    	printf("NotFind\n");    
    }

    _removeAll();
    for(int i=1;i<=N;++i){
      adj[i].clear();
    }
    printf("\n");
  }
  return 0;
}
