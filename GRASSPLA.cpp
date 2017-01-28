#include <bits/stdc++.h>
#define NMAX 111111
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)
using namespace std;

int N,M;

struct node{
  int lazy,sum;

  node(int a=0,int b=0){
    sum=a;lazy=b;
  }
};

struct segTree{
  vector<node> tree;
  int sz,value;

  segTree(int _sz){
    sz=_sz;
    tree=vector<node>(sz<<2);
    build(1,1,sz);
  }

  void merge(node a,node b,node &c){
    c.sum=a.sum+b.sum;
  }

  void modify(int index,int len,int val){
    tree[index].lazy+=val;
    tree[index].sum+=(val*len);
  }

  void push(int index,int i,int j){
    if(i!=j){
      if(tree[index].lazy){
	int mid=(i+j)>>1;
	modify(L(index),mid-i+1,tree[index].lazy);
	modify(R(index),j-mid,tree[index].lazy);
	tree[index].lazy=0;
      }
    }
  }

  void build(int index,int i,int j){
    tree[index]=node();
    if(i<j){
      int mid=(i+j)>>1;
      build(L(index),i,mid);
      build(R(index),mid+1,j);
    }
  }
  
  void update(int index,int i,int j,int st,int en){
    if(i==st && j==en){
      modify(index,j-i+1,value);
      return;
    }
    push(index,i,j);

    int mid=(i+j)>>1;
    if(en<=mid) update(L(index),i,mid,st,en);
    else if(st>mid) update(R(index),mid+1,j,st,en);
    else{
      update(L(index),i,mid,st,mid);
      update(R(index),mid+1,j,mid+1,en);
    }
    merge(tree[L(index)],tree[R(index)],tree[index]);
  }

  node query(int index,int i,int j,int st,int en){
    if(i==st && j==en) return tree[index];
    push(index,i,j);

    int mid=(i+j)>>1;
    if(en<=mid) return query(L(index),i,mid,st,en);
    else if(st>mid) return query(R(index),mid+1,j,st,en);
    else{
      node tmp;
      merge(query(L(index),i,mid,st,mid),query(R(index),mid+1,j,mid+1,en),tmp);
      return tmp;
    }
  }

  void update(int st,int en,int val){
    value=val;
    if(st>0 && en<=sz && st<=en)
      update(1,1,sz,st,en);
  }

  int query(int st,int en){
    if(st>0 && en<=sz && st<=en)
      return query(1,1,sz,st,en).sum;
    return 0;
  }
};

const int L = 19;
int p[NMAX][L];
int _log;
int ti[NMAX], to[NMAX], _tm;
int h[NMAX];

void buildLCA(){
  for(_log=0; 1<<_log<N; ++_log);
  ++_log;
  _tm = 0;
}

bool upper(int v, int u){
  return v==-1 || u!=-1 && ti[v]<ti[u] && to[v]>to[u];
}

int lca(int v, int u){
  if(v==u || upper(v,u)) return v;
  if(upper(u,v)) return u;
  for(int i=_log-1;i>=0;--i) if(!upper(p[v][i], u)) v = p[v][i];
  return p[v][0];
}
        
int nextDownTo(int from, int downto){
  for(int i=_log-1;i>=0;--i) if(upper(from, p[downto][i])) downto = p[downto][i];
  return downto;
}

vector<int> adj[NMAX];
int subt[NMAX];

inline void addEdge(int u,int v){
  adj[u].push_back(v);
  adj[v].push_back(u);
}


int dfs(int u,int par){
  ti[u] = ++_tm;
  p[u][0] = par;
  h[u] = (par==-1 ? 0 : h[par]+1);
  subt[u]=1;
  for(int i=1;i<_log;++i)
    p[u][i] = (p[u][i-1]==-1 ? -1: p[p[u][i-1]][i-1]);

  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];
    if(v!=par) subt[u]+=dfs(v,u);
  }

  to[u] = ++_tm;
  return subt[u];
}

// End Graph Routines
//--------------------------------------------------------------------------
// Begin HLD Functions

vector<segTree*> trees;
vector<int> chain[NMAX];
int chId[NMAX], chPos[NMAX],chHd[NMAX];
int chNum;

int q[NMAX<<2], qn;

int hld(int u,int p){
  if(chain[chNum].size()==0) chHd[chNum]=u;
  chain[chNum].push_back(u);
  chId[u]=chNum; chPos[u]=chain[chNum].size();

  int most,ind;
  most = 0; ind = -1;
  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];
    if(v!=p && subt[v]>most) most=subt[v], ind=v;
  }

  if(ind!=-1) hld(ind,u);
  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];
    if(v!=ind && v!=p){
      ++chNum;
      hld(v,u);
    }
  }

}

void getPath(int from, int to){
  qn=0;
  for(;;){
    int fi = chId[from];
    int end = chHd[fi];
    if(fi==chId[to]) end = to;
    q[qn++]=fi;
    q[qn++]=chPos[end];
    q[qn++]=chPos[from];
    if(end==to) break;
    from = p[end][0];
  }
}

void buildSegTrees(){
  for(int i=0;i<=chNum;++i){
    segTree *tmp = new segTree(chain[i].size());
    trees.push_back(tmp);
  }
}

void changePath(int u,int l,int val){
  getPath(u,l);
  for(int i=0;i<qn;i+=3){
    //cout << q[i] << " " << q[i+1] << " " << q[i+2] << endl;
    int id=q[i];
    trees[id]->update(q[i+1],q[i+2],val);
  }
}

int queryPath(int u,int l){
  int res=0;
  getPath(u,l);
  for(int i=0;i<qn;i+=3){
    //cout << q[i] << " " << q[i+1] << " " << q[i+2] << endl;
    res += trees[q[i]]->query(q[i+1],q[i+2]);
  }
  return res;
}

void solve(){
  buildLCA();
  dfs(1,-1);
  chNum=0;
  hld(1,-1);
  buildSegTrees();

  // for(int i=0;i<=chNum;++i){
  //   cout << i << endl;
  //   for(int j=0;j<chain[i].size();++j)
  //     cout << chain[i][j] << " ";
  //   cout << endl;
  // }

  char buf[3];
  int u,v,val,lc;

  for(int i=0;i<M;++i){
    scanf("%s %d %d",buf,&u,&v);
    assert(u!=v);
    lc = lca(u,v);

    if(buf[0]=='Q'){
      int res = 0;
      if(u!=lc) res += queryPath(u,nextDownTo(lc,u));
      if(v!=lc) res += queryPath(v,nextDownTo(lc,v));
      printf("%d\n",res);
    }
    else{
      if(u!=lc) changePath(u,nextDownTo(lc,u),1);
      if(v!=lc) changePath(v,nextDownTo(lc,v),1);
    }

    // for(int i=0;i<=chNum;++i){
    //   cout << i << endl;
    //   trees[i]->debug();
    // }
      
  }
}



int main(){
  int u,v;
  scanf("%d %d",&N,&M);
  for(int i=0;i<N-1;++i){
    scanf("%d %d",&u,&v);
    addEdge(u,v);
  }
  solve();
  return 0;
}
