#include <bits/stdc++.h>
#define NMAX 111111
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)
#define inf NMAX<<4
using namespace std;

multiset<int> dist[NMAX];
vector<int> adj[NMAX];
int subt[NMAX],parent[NMAX],color[NMAX];
int N,M;

inline void addEdge(int u,int v){
  adj[u].push_back(v);
  adj[v].push_back(u);
}

void dfs(int u,int p){
  subt[u]=1;
  parent[u]=p;
  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];
    if(v!=p){
      dfs(v,u);
      subt[u]+=subt[v];
    }
  }
}

struct node{
  int lmin,rmin,id;
  int sz;

  node(int a=0,int b=0,int c=inf,int d=inf){
    id=a; sz=b;
    lmin=c; rmin=d;
  }

};

struct segTree{
  vector<node> tree;
  vector<int> A;
  int sz;
  int pos;

  segTree(vector<int> _A){
    A=vector<int>(_A);
    sz=A.size();
    tree=vector<node>(sz<<2);
    build(1,1,sz);
  }

  void modify(int index){
    int val;
    int u=tree[index].id;
    if(color[u]==1) val=0;
    else if(dist[u].size()==0) val=inf;
    else val=*dist[u].begin();

    tree[index].lmin=tree[index].rmin=val;
  }

  void merge(node a,node b,node &c){
    c.lmin=min(a.lmin, b.lmin+a.sz);
    c.rmin=min(b.rmin, a.rmin+b.sz);
  }

  void build(int index,int i,int j){
    tree[index].sz=j-i+1;
    if(i==j){
      tree[index].id=A[i-1];
      modify(index);
      return;
    }
    int mid=(i+j)>>1;
    build(L(index),i,mid);
    build(R(index),mid+1,j);
  }

  void update(int index,int i,int j){
    if(i==j && i==pos){
      modify(index);
      return;
    }
    int mid=(i+j)>>1;
    if(pos<=mid) update(L(index),i,mid);
    else update(R(index),mid+1,j);

    merge(tree[L(index)],tree[R(index)],tree[index]);
  }

  node query(int index,int i,int j,int st,int en){
    if(i==st && j==en) return tree[index];
    int mid=(i+j)>>1;
    if(en<=mid) return query(L(index),i,mid,st,en);
    else if(st>mid) return query(R(index),mid+1,j,st,en);
    else{
      node tmp(0,en-st+1);
      merge(query(L(index),i,mid,st,mid),query(R(index),mid+1,j,mid+1,en),tmp);
      return tmp;
    }
  }

  void update(int p){
    pos=p;
    update(1,1,sz);
  }

  node query(int st,int en){
    return query(1,1,sz,st,en);
  }

  void debug(){
    cout << "----------------------------------" << endl;
    printTree(1,1,sz);
    cout << "----------------------------------" << endl;
  }

  void printTree(int index,int i,int j){
    if(i==j){
      cout << "(" << i << "," << j << ") " <<tree[index].lmin << " " << tree[index].rmin << " " << tree[index].id << endl;
      return;
    }
    int mid=(i+j)>>1;
    printTree(L(index),i,mid);
    printTree(R(index),mid+1,j);
    cout << "(" << i << "," << j << ") " <<tree[index].lmin << " " << tree[index].rmin << " " << tree[index].id << endl;
  }

};

vector<segTree> chains;
vector<int> chVal[NMAX];
int chId[NMAX],chPos[NMAX],chHd[NMAX];
int chNum;

void hld(int u,int p){
  if(chVal[chNum].size()==0) chHd[chNum]=u;
  chVal[chNum].push_back(u);
  chId[u]=chNum;
  chPos[u]=chVal[chNum].size();

  int most=0,ind=-1;

  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];
    if(v!=p && subt[v]>most) most=subt[v],ind=v;
  }

  if(ind!=-1) hld(ind,u);
  for(int i=0;i<adj[u].size();++i){
    int v=adj[u][i];
    if(v!=p && v!=ind){
      ++chNum;
      hld(v,u);
    }
  }
  
}

void buildSegTrees(){
  for(int i=0;i<=chNum;++i){
    segTree tmp(chVal[i]);
    chains.push_back(tmp);
  }
}

void update(int u){
  int idx,pos,oldVal,newVal;
  multiset<int>::iterator pt;

  color[u]=1^color[u];
  while(u!=-1){
    idx=chId[u];pos=chPos[u];
    oldVal = chains[idx].query(1,chains[idx].sz).lmin+1;
    chains[idx].update(pos);
    newVal = chains[idx].query(1,chains[idx].sz).lmin+1;

    if(parent[chHd[idx]]==-1) break;

    u=parent[chHd[idx]];
    if((pt=dist[u].find(oldVal))!=dist[u].end())
      dist[u].erase(pt);
    dist[u].insert(newVal);
  }
}

int query(int u){
  int node=u;
  int idx,pos,curr,off,res=inf;
  off=0;
  while(node!=-1){
    idx=chId[node]; pos=chPos[node];
    curr=min(chains[idx].query(1,pos).rmin+off,chains[idx].query(pos,chains[idx].sz).lmin+off);
    res=min(curr,res);
    off += pos;
    node=parent[chHd[idx]];
  }
  if( res == inf ) res = -1;
  return res;
}

int main(){
  int u,v;
  scanf("%d",&N);
  for(int i=0;i<N-1;++i){
    scanf("%d %d",&u,&v);
    addEdge(u,v);
  }

  dfs(1,-1);
  chNum=0;
  hld(1,-1);
  buildSegTrees();

  //for(int i=0;i<=chNum;++i) chains[i].debug();

  scanf("%d",&M);
  for(int i=0;i<M;++i){
    scanf("%d %d",&u,&v);
    if(u==0) update(v);
    else{ printf("%d\n",query(v));
      // for(int i=0;i<=chNum;++i) chains[i].debug();
      // node tmp;
      
      // chains[0].merge(chains[0].query(2,3),chains[0].query(4,4),tmp);
      // cout << "HERE"<<tmp.lmin << endl;
    }
  }

  return 0;
}
