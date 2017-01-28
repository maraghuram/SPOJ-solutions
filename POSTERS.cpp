#include <bits/stdc++.h>
#define NMAX 44444
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)
#define inf NMAX<<2
using namespace std;
typedef pair<int,int> pii;

struct node{
  int lazy,lazyind,mx,ind;
  bool set;
  node(){
    lazy=0;mx=0;
    set=false;
  }
}tree[NMAX<<8];

void modify(int index,int val,int node){
  if(val>tree[index].mx) tree[index].mx=val, tree[index].ind=node;
  tree[index].set=true;tree[index].lazy=val;tree[index].lazyind=node;
}

void push(int index,int i,int j){
  if(i!=j){
    if(tree[index].set){
      modify(L(index),tree[index].lazy,tree[index].lazyind);
      modify(R(index),tree[index].lazy,tree[index].lazyind);
      tree[index].set=false;
    } 
  }
}

node merge(node x,node y){
  node tmp;
  if(x.mx>y.mx) tmp.mx=x.mx, tmp.ind=x.ind;
  else tmp.mx=y.mx, tmp.ind=y.ind;
  return tmp;
}

int value,pos;

void update(int index,int i,int j,int st,int en){
  if(st==i && en==j){
    modify(index,value,pos);
    return;
  }
  push(index,i,j);
  int mid=(i+j)>>1;
  if(en<=mid) update(L(index),i,mid,st,en);
  else if(st>mid) update(R(index),mid+1,j,st,en);
  else {
    update(L(index),i,mid,st,mid);
    update(R(index),mid+1,j,mid+1,en);
  }
  tree[index]=merge(tree[L(index)],tree[R(index)]);
}

node query(int index,int i,int j,int st,int en){
  if(i==st && j==en) return tree[index];
  push(index,i,j);
  int mid=(i+j)>>1;
  if(en<=mid) return query(L(index),i,mid,st,en);
  else if(st>mid) return query(R(index),mid+1,j,st,en);
  else return merge(query(L(index),i,mid,st,mid),query(R(index),mid+1,j,mid+1,en));
}

void build(int index,int i,int j){
  tree[index].lazy=0;tree[index].mx=0;tree[index].set=false;
  if(i==j) return;
  int mid=(i+j)>>1;
  build(L(index),i,mid);
  build(R(index),mid+1,j);
}

int main(){
  int t;
  scanf("%d",&t);
  for(int tc=0;tc<t;++tc){
    int u,v;
    vector<pii> ranges;
    vector<int> mix;
    int n,res=0;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
      scanf("%d %d",&u,&v);
      ranges.push_back(pii(u,v));
      mix.push_back(u);mix.push_back(v);
    }
    sort(mix.begin(),mix.end());
    mix.erase(unique(mix.begin(),mix.end()),mix.end());

    int sz=mix.size();

    build(1,1,sz);
    for(int i=0;i<n;++i){
      u=lower_bound(mix.begin(),mix.end(),ranges[i].first)-mix.begin()+1;
      v=lower_bound(mix.begin(),mix.end(),ranges[i].second)-mix.begin()+1;
      value=i+1; pos=i;
      update(1,1,sz,u,v);
    }

    vector<int> flag(n,0);
    
    for(int i=0;i<sz;++i)
      flag[query(1,1,sz,i+1,i+1).ind]=1;
    for(int i=0;i<n;++i) if(flag[i]) ++res;

    printf("%d\n",res);
    
  }
 
  return 0;
}
