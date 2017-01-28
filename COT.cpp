#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<vector>
#define NMAX 111111
#define LMAX 21
using namespace std;
typedef long long int ll;

inline int read_int() {
  register char c = getchar_unlocked();
  while(c<'0' || c>'9') c = getchar_unlocked();
  int ret = 0;
  while(c>='0' && c<='9') {
    ret = (ret<<3)+(ret<<1) + c - 48;
    c = getchar_unlocked();
  }
  return ret;
}

struct node{
  node *l, *r;
  int cnt;
  node(){
    l=r=NULL;
    cnt=0;
  }
};

node *root[NMAX];
vector<int> adjList[NMAX];
int par[NMAX][LMAX],depth[NMAX],weight[NMAX];
int N,Q;

node* build(int i,int j){
  node *newNode = new node();
  if(i!=j){
    int mid=(i+j)>>1;
    newNode->l = build(i,mid);
    newNode->r = build(mid+1,j);
  }
  return newNode;
}

node *update(node *index,int i,int j,int pos){
  node *newNode = new node();
  newNode->l = index->l, newNode->r = index->r, newNode->cnt = index->cnt;
  if(i==j && i==pos){
    newNode->cnt += 1;
    return newNode;
  }
  int mid=(i+j)>>1;
  if( pos<=mid ) newNode->l = update(index->l,i,mid,pos);
  else newNode->r = update(index->r,mid+1,j,pos);
  
  newNode->cnt = newNode->l->cnt + newNode->r->cnt;
  return newNode;
}

int query(node *u,node *v,node *lc,int i,int j,int k,int extra){
  if( u->l == NULL ) return i;
  int lsum = u->l->cnt + v->l->cnt - 2*lc->l->cnt;
  int mid=(i+j)>>1;
  if( i<= extra && extra<=mid ) ++lsum;
  //  cout<<i<<","<<j<<" "<<k<<" "<<extra<<" -- "<<lsum<<endl;
  if( k<=lsum ) return query( u->l,v->l,lc->l,i,mid,k,extra);
  else return query(u->r,v->r,lc->r,mid+1,j,k-lsum,extra);
}

void dfs(int u,int p,int d){
  par[u][0]=p;
  depth[u]=d;
  root[u] = update(root[p],1,N,weight[u]);
  for(int i=0;i<adjList[u].size();++i){
    int v = adjList[u][i];
    if(v!=p) dfs(v,u,d+1);
  }
}

void buildLca(){
  for(int j=0;j<LMAX;++j)
      par[0][j]=0;
  
  for (int j = 0; j < LMAX; ++ j) 
    for (int i = 1; i <= N; i++)
      if (par[i][j - 1] != 0)
	par[i][j] = par[par[i][j - 1]][j - 1];
}

int jump(int u, int d) {
    for (int i = 0; i < LMAX; ++ i) {
        if (d >> i & 1) {
            u = par[u][i];
        }
    }
    return u;
}


int queryLca(int p,int q){
  int tmp, log, i;
  if (depth[p] < depth[q])
    tmp = p, p = q, q = tmp;
  for (log = 1; 1 << log <= depth[p]; log++);
  log--;
   
  for (i = log; i >= 0; i--)
    if (depth[p] - (1 << i) >= depth[q])
      p = par[p][i];
  if (p == q)
    return p;
  for (i = log; i >= 0; i--)
    if (par[p][i] != 0 && par[p][i] != par[q][i])
      p = par[p][i], q = par[q][i];
   
  return par[p][0];
}

int main(){
  //scanf("%d %d",&N,&Q);
  N = read_int();
  Q = read_int();

  vector<int> A(N),B(N);
  for(int i=0;i<N;++i){
    //scanf("%d",&A[i]);
    A[i] = read_int();
    B[i]=A[i];
  }

  sort(B.begin(),B.end());
  B.erase(unique(B.begin(),B.end()),B.end());
  for(int i=0;i<N;++i) weight[i+1] = lower_bound( B.begin(),B.end(),A[i] ) - B.begin() + 1;

  for(int i=0;i<N-1;++i){
    int u,v;
    //scanf("%d %d",&u,&v);
    u = read_int();
    v = read_int();
    adjList[u].push_back(v);
    adjList[v].push_back(u);
  }

  root[0]=build(1,N);
  dfs(1,0,0);  
  buildLca();
  for(int q=0;q<Q;++q){
    int i,j,k;
    //scanf("%d %d %d",&i,&j,&k);
    i = read_int();
    j = read_int();
    k = read_int();
    int lc = queryLca(i,j);
    //cout<<lc<<endl;
    printf("%d\n",B[query(root[i],root[j],root[lc],1,N,k,weight[lc])-1]);
  }

  return 0;
}
