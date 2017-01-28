#include <bits/stdc++.h>
#define NMAX 111111
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)
#define MOD 1000000007
using namespace std;
typedef long long int ll;

ll powR[NMAX],sumR[NMAX];

struct node{
  ll lazy,sum;
  node(int b=0,int c=0){
    sum=b; lazy=c;
  }
}tree[NMAX<<2];

void modify(int index,int sz,ll val){
  tree[index].sum += (val*sumR[sz])%MOD;
  tree[index].sum %= MOD;
  tree[index].lazy += val;
  tree[index].lazy %= MOD;
}

void push(int index,int i,int j){
  if(i!=j){
    ll tmp=tree[index].lazy;
    if(tmp){
      int mid=(i+j)>>1;
      modify(L(index),mid-i+1,tmp);
      modify(R(index),j-mid,(tmp*powR[mid-i+1])%MOD);
      tree[index].lazy=0;
    }
  }
}

void merge(node x,node y,node &z){
  z.sum = (x.sum + y.sum)%MOD;
}

void build(int index,int i,int j){
  tree[index]=node();
  if(i<j){
    int mid=(i+j)>>1;
    build(L(index),i,mid);
    build(R(index),mid+1,j);
  }
}

ll value;
int _st,_en;

void update1(int index,int i,int j,int st,int en){
  if(i==st && j==en){
    modify(index,j-i+1,(value*powR[i-_st])%MOD);
    return;
  }
  push(index,i,j);
  int mid=(i+j)>>1;
  
  if(en<=mid) update1(L(index),i,mid,st,en);
  else if(st>mid) update1(R(index),mid+1,j,st,en);
  else{
    update1(L(index),i,mid,st,mid);
    update1(R(index),mid+1,j,mid+1,en);
  }
  merge(tree[L(index)],tree[R(index)],tree[index]);
}

void update2(int index,int i,int j,int pos){
  if(i==j && i==pos){
    tree[index].lazy=tree[index].sum=0;
    return;
  }
  push(index,i,j);
  int mid=(i+j)>>1;
  
  if(pos<=mid) update2(L(index),i,mid,pos);
  else update2(R(index),mid+1,j,pos);

  merge(tree[L(index)],tree[R(index)],tree[index]);
}

ll query(int index,int i,int j,int st,int en){
  if(i==st && j==en) return tree[index].sum;
  push(index,i,j);
  int mid=(i+j)>>1;
  
  if(en<=mid) return query(L(index),i,mid,st,en);
  else if(st>mid) return query(R(index),mid+1,j,st,en);
  else
    return (query(L(index),i,mid,st,mid)+query(R(index),mid+1,j,mid+1,en))%MOD;
}

void printTree(int index,int i,int j){
  if(i==j){
    printf("%d,%d %lld %lld\n",i,j,tree[index].sum,tree[index].lazy);
    return ;
  }
  int mid=(i+j)>>1;
  printTree(L(index),i,mid);
  printTree(R(index),mid+1,j);
  printf("%d,%d %lld %lld\n",i,j,tree[index].sum,tree[index].lazy);
}

int N,Q;
ll R;

void debug(){
  cout << "-----------------" << endl;
  printTree(1,1,N);
  cout << "-----------------" << endl;
}

int main(){

  scanf("%d %lld %d",&N,&R,&Q);
  R=R%MOD;
  powR[0]=1;sumR[0]=0;
  for(int i=1;i<=N;++i){
    powR[i]=(powR[i-1]*R)%MOD;
    sumR[i]=(sumR[i-1]+powR[i-1])%MOD;
  }
  build(1,1,N);

  int ty,u,v;
  for(int i=0;i<Q;++i){
    scanf("%d",&ty);
    if(ty==0){
      scanf("%lld %d %d",&value,&u,&v);
      value=value%MOD;
      assert(u<=v);
      _st=u;_en=v;
      update1(1,1,N,u,v);
    }
    else if(ty==1){
      scanf("%d %d",&u,&v);
      assert(u<=v);
      printf("%lld\n",query(1,1,N,u,v));
    }
    else{
      scanf("%d",&u);
      update2(1,1,N,u);
    }
    //debug();
  }


  return 0;
}
