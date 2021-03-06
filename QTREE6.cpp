#include <bits/stdc++.h>
#define NMAX 111111
#define L(x) ( x<<1 )
#define R(x) ( (x<<1 ) + 1)
#define pb push_back
#define sz size( )
#define CL(S,x) memset(S,x,sizeof(S))
#define FOR(i,x,y) for(i=x;i<=y;i++)
#define _FOR(i,x,y) for(i=x;i>=y;i--)
#define inf 999999999

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
  int col;
  int pos[2];
};

struct node2{
  ll lazy[2];
  ll sum[2];
};

vector<int> adjList[NMAX];
int subtree[NMAX], parent[NMAX], color[NMAX];
int n1, Q;

struct hlChain{
  vector<node> tree;
  vector<node2> tree2;
  vector<int> subt,inp;
  int N, col;
  ll val;

  hlChain( vector<int> input ){
    N = input.sz;
    inp = input;
    subt = vector<int>(N+1);
    for(int i=0;i<N;++i) subt[i] = subtree[input[i]]; 
    tree = vector<node>(N<<2);
    tree2 = vector<node2>(N<<2);

    init(1,0,N-1);
    init2(1,0,N-1);
  }

  node merge(node x,node y,int mid){
    node z;
    z.col=0;
    z.pos[0] = (y.pos[0]==(mid+1))?min(mid+1,x.pos[0]):y.pos[0];
    z.pos[1] = (y.pos[1]==(mid+1))?min(mid+1,x.pos[1]):y.pos[1];
    return z;
  }

  void init(int idx,int i,int j){
    if(i==j) {
      tree[idx].col=0;
      tree[idx].pos[0]=i;
      tree[idx].pos[1]=inf;
      return;
    }
    int mid=(i+j)>>1;
    
    init(L(idx),i,mid);
    init(R(idx),mid+1,j);
  
    tree[idx] = merge( tree[L(idx)], tree[R(idx)], mid );
  }
  
  void update(int idx,int i,int j,int pt,int val){
    if(i==j && i==pt){
    tree[idx].col = val;
    tree[idx].pos[val]=i;
    tree[idx].pos[1^val]=inf;
    return;
    }
    int mid=(i+j)>>1;
    
    if(pt<=mid) update(L(idx),i,mid,pt,val);
    else update(R(idx),mid+1,j,pt,val);
    tree[idx] = merge( tree[L(idx)], tree[R(idx)], mid );
  }
  
  node query(int idx,int i,int j,int left,int right){
    if(i==left && j==right) return tree[idx];
    int mid=(i+j)>>1;
    
    if(right<=mid) return query(L(idx),i,mid,left,right);
    else if(left>mid) return query(R(idx),mid+1,j,left,right);
    else{
      node res1 = query(L(idx),i,mid,left,mid);
      node res2 = query(R(idx),mid+1,j,mid+1,right);
      return merge( res1, res2, mid);
    }
  }
  
  void propagate( int idx,int i,int j ){
    tree2[idx].sum[0] += (tree2[idx].lazy[0]*(j-i+1));
    tree2[idx].sum[1] += (tree2[idx].lazy[1]*(j-i+1));
    if(i!=j){
      tree2[L(idx)].lazy[0] += tree2[idx].lazy[0];
      tree2[L(idx)].lazy[1] += tree2[idx].lazy[1];
      tree2[R(idx)].lazy[0] += tree2[idx].lazy[0];
      tree2[R(idx)].lazy[1] += tree2[idx].lazy[1];
    }
    tree2[idx].lazy[0]=tree2[idx].lazy[1]=0;
  }

  void init2( int idx,int i,int j ){
    if(i==j) {
      tree2[idx].sum[0]=(ll)subt[i] - 1;
      tree2[idx].lazy[0]=tree2[idx].lazy[1]=tree2[idx].sum[1]=0;
      return;
    }
    int mid=(i+j)>>1;
    init2(L(idx),i,mid);
    init2(R(idx),mid+1,j);
    tree2[idx].sum[0]=tree2[L(idx)].sum[0] + tree2[R(idx)].sum[0];
    tree2[idx].sum[1]=tree2[L(idx)].sum[1] + tree2[R(idx)].sum[1];
    tree2[idx].lazy[0]=tree2[idx].lazy[1]=0;
  }
  
  void update2(int idx,int i,int j,int left,int right){
    propagate(idx,i,j);
    if( left<=i && j<=right ){
      tree2[idx].sum[col] += ( val * (j-i+1));
      if(i!=j){
	tree2[L(idx)].lazy[col] += val;
	tree2[R(idx)].lazy[col] += val;
      }
      return;
    }
    if(left>j || right<i) return;
    
    int mid= (i+j)>>1;
    update2(L(idx),i,mid,left,right);
    update2(R(idx),mid+1,j,left,right);
    
    tree2[idx].sum[0]=tree2[L(idx)].sum[0] + tree2[R(idx)].sum[0];
    tree2[idx].sum[1]=tree2[L(idx)].sum[1] + tree2[R(idx)].sum[1];
  }
  
  ll query2(int idx,int i,int j,int left,int right){
    propagate(idx,i,j);
    if( left<=i && j<=right ) return tree2[idx].sum[col];
    if(left>j || right<i) return 0;
    
    int mid= (i+j)>>1;
    ll res1 = query2(L(idx),i,mid,left,right);
    ll res2 = query2(R(idx),mid+1,j,left,right);
    
    tree2[idx].sum[0]=tree2[L(idx)].sum[0] + tree2[R(idx)].sum[0];
    tree2[idx].sum[1]=tree2[L(idx)].sum[1] + tree2[R(idx)].sum[1];
    return res1 + res2;
  }

  void printTree( int idx,int i,int j){
    if(i==j){
      cout<<i<<","<<j<<" "<<tree[idx].pos[0]<<" "<<tree[idx].pos[1]<<endl;
      return;
    }
    int mid=(i+j)>>1;
    printTree(L(idx),i,mid);
    printTree(R(idx),mid+1,j);
    cout<<i<<","<<j<<" "<<tree[idx].pos[0]<<" "<<tree[idx].pos[1]<<endl;
  }
  void printTree2( int idx,int i,int j){
    if(i==j){
      cout<<i<<","<<j<<" "<<tree2[idx].sum[0]<<" "<<tree2[idx].sum[1]<<"-->"<<tree2[idx].lazy[0]<<" "<<tree2[idx].lazy[1]<<endl;
      return;
    }
    int mid=(i+j)>>1;
    printTree2(L(idx),i,mid);
    printTree2(R(idx),mid+1,j);
    cout<<i<<","<<j<<" "<<tree2[idx].sum[0]<<" "<<tree2[idx].sum[1]<<"-->"<<tree2[idx].lazy[0]<<" "<<tree2[idx].lazy[1]<<endl;
  }

  node query(int left,int right){
    return query(1,0,N-1,left,right);
  }

  ll query2(int left,int right,int col_){
    col= col_;
    return query2(1,0,N-1,left,right);
  }

  void update(int point,int value){
    update(1,0,N-1,point,value);
  }
  
  void update2(int left,int right,int col_,ll val_){
    col=col_;
    val=val_;
    update2(1,0,N-1,left,right);
  }
};

vector<hlChain> chains;
vector< vector<int> > chainVal;
int chainPos[NMAX], chainId[NMAX], chainHead[NMAX];
int cnum;

int dfs( int u,int p ){
  subtree[u] = 1;
  parent[u] = p;
  color[u]=0;
  for(int i=0;i<adjList[u].sz;++i){
    int v=adjList[u][i];
    if( v!=p ) subtree[u] += dfs(v,u);
  }
  return subtree[u];
}

void hld(int u,int p){
  chainVal[cnum].pb(u);
  chainPos[u] = chainVal[cnum].sz-1;
  chainId[u] = cnum;
  if( chainPos[u] == 0 ) chainHead[cnum] = u;
  
  int most,idx;
  most = idx =-1;
  for(int i=0;i<adjList[u].sz;++i){
    int v=adjList[u][i];
    if( v!=p && subtree[v] > most ) most=subtree[v], idx=v;
  } 
  if( idx != -1 ) hld(idx,u);
  for(int i=0;i<adjList[u].sz;++i){
    int v=adjList[u][i];
    if( v!=p && v!=idx){
      ++cnum;
      chainVal.pb(vector<int>(0));
      hld(v,u);
    }
  }
}

int lowestWithSameCol( int u ){
  int x = u;
  int col = color[u];
  int pos = chainPos[u];
  int idx = chainId[u];
  node low;  

  while(1){
    low = chains[idx].query(0,pos);
    if(low.pos[col]!=0) return chains[idx].inp[low.pos[col]];
    x = parent[chainHead[idx]];
    if(x==-1 || color[x]!=col) return chainHead[idx];
    pos = chainPos[x];
    idx = chainId[x];
  }
}

ll ask( int u ){
  int top = lowestWithSameCol(u);
  int idx = chainId[top];
  int pos = chainPos[top];
  return chains[idx].query2(pos,pos,color[u]) + 1;
}

ll change1( int u ){
  int x = u;
  int oldCol = color[u];
  int newCol = 1^oldCol;

  int pos = chainPos[u];
  int idx = chainId[u];
  ll sub,add;
  node low;

  sub = -( chains[idx].query2(pos,pos,oldCol) + 1);
  add = chains[idx].query2(pos,pos,newCol)+1;

  x = parent[u];  
  if( x!=-1 && color[x] == oldCol ){
    pos = chainPos[x];
    idx = chainId[x];
    while( 1 ){
      low = chains[idx].query(0,pos);    
      chains[idx].update2(low.pos[oldCol],pos,oldCol,sub);
      if( low.pos[oldCol] !=0 ){
	x = chains[idx].inp[low.pos[oldCol]-1];
	idx = chainId[x], pos = chainPos[x];
	break;
      }
      x = parent[chainHead[idx]];
      if(x==-1) break;
      idx = chainId[x], pos = chainPos[x];     
      if(color[x]!=oldCol) break;
    }
  }

  if( x!=-1 ){
    pos = chainPos[x],idx=chainId[x];
    chains[idx].update2(pos,pos,oldCol,sub);
  }

  pos=chainPos[u], idx=chainId[u];
  //cout<< newCol << " ---< " <<endl;
  color[u] = 1^color[u];
  chains[idx].update( pos,newCol );
  //x = u;
  
  x = parent[u];  
  if( x!=-1 && color[x] == newCol ){
    pos = chainPos[x];
    idx = chainId[x];
    while( 1 ){      
      low = chains[idx].query(0,pos);    
      chains[idx].update2(low.pos[newCol],pos,newCol,add);
      if( low.pos[newCol] !=0 ){
	x = chains[idx].inp[low.pos[newCol]-1];
	idx = chainId[x], pos = chainPos[x];
	break;
      }
      x = parent[chainHead[idx]];
      if(x==-1) break;
      idx = chainId[x], pos = chainPos[x];     
      if(color[x]!=newCol) break;
    }
  }
  if( x!=-1 ){
    pos = chainPos[x], idx = chainId[x];
    chains[idx].update2(pos,pos,newCol,add);
  }
}  


void solve(){  
  cnum = 0;
  chainVal.pb(vector<int>(0));
  dfs(1,-1);
  hld(1,-1);
  for(int i=0;i<=cnum;++i){
    //for(int j=0;j<chainVal[i].sz;++j)
    // cout<<chainVal[i][j]<<" ";
    //cout<< endl;
    hlChain x(chainVal[i]);
    chains.pb(x);
  }
  
  Q = read_int();
  //scanf("%d",&Q);
  for(int i=0;i<Q;++i){
    int type,u;
    type =read_int();
    u = read_int();
    //scanf("%d %d",&type,&u);
    if(type == 0) {
      printf("%lld\n",ask(u));
    }
    else{
      change1(u);            
      //                  cout<<"---><>"<<endl;
      //                  chains[chainId[u]].printTree2(1,0,chains[chainId[u]].N-1);
    }
  }

  
}

int main(){
  n1 = read_int();

  for(int i=0;i<n1-1;++i){
    int u,v;
    u = read_int();
    v = read_int();
    adjList[u].pb(v);
    adjList[v].pb(u);
  }
  
  solve();

  return 0;
}
