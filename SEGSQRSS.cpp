#include <bits/stdc++.h>
#define NMAX 111111
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)

using namespace std;
typedef long long int ll;

int N,Q;
ll A[NMAX];

struct node{
  ll sqSum,sum;
  ll lazya,lazyb;
  bool set;
  node(){
    sqSum=sum=lazya=lazyb=0;
    set=false;
  }
}tree[NMAX<<4];

ll value;

node merge(node x,node y){
  node tmp;
  tmp.sqSum = x.sqSum + y.sqSum;
  tmp.sum = x.sum + y.sum;
  return tmp;
}

void build(int index,int i,int j){
  if(i==j){
    tree[index].sqSum = A[i-1]*A[i-1];
    tree[index].sum = A[i-1];
    return;
  }
  int mid=(i+j)>>1;
  build(L(index),i,mid);
  build(R(index),mid+1,j);
  tree[index]=merge(tree[L(index)],tree[R(index)]);
}

void set0(int index,int len,ll val){
  tree[index].set=true;
  tree[index].lazya=val;
  tree[index].lazyb=0;
  tree[index].sqSum = val*val*len;
  tree[index].sum = val*len;
}

void set1(int index,int len,int val){
  tree[index].lazyb=val;
  tree[index].sqSum += (2*len*val + len*val*val);
  tree[index].sum += (len*val);
}

void push(int index,int i,int j){
  if(i!=j){
    int mid=(i+j)>>1;
    if(tree[index].set){
      set0(L(index),mid-i+1,tree[index].lazya);
      set0(R(index),j-mid, tree[index].lazya);
      tree[index].set=false;
    }
    set1(L(index),mid-i+1,tree[index].lazyb);
    set1(R(index),j-mid,tree[index].lazyb);
  }
}


void update0(int index,int i,int j,int st,int en){
  if(i==st && j==en){
    set0(index,j-i+1,value);
    return;
  }
  push(index,i,j);
  int mid=(i+j)>>1;
  if(en<=mid) update0(L(index),i,mid,st,en);
  else if(st>mid) update0(R(index),mid+1,j,st,en);
  else{
    update0(L(index),i,mid,st,mid);
    update0(R(index),mid+1,j,mid+1,en);
  }
  tree[index]=merge(tree[L(index)],tree[R(index)]);
}

void update1(int index,int i,int j,int st,int en){
  if(i==st && j==en){
    set1(index,j-i+1,value);
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

  tree[index]=merge(tree[L(index)],tree[R(index)]);
}

ll query(int index,int i,int j,int st,int en){
  if(i==st && j==en) return tree[index].sqSum;
  push(index,i,j);
  int mid=(i+j)>>1;
  if(en<=mid) return query(L(index),i,mid,st,en);
  else if(st>mid) return query(R(index),mid+1,j,st,en);
  else return query(L(index),i,mid,st,mid)+query(R(index),mid+1,j,mid+1,en);
}

void printTree(int index,int i,int j){
  if(i==j){
    printf("%d,%d %lld %lld %lld %lld\n",i,j,tree[index].sqSum,tree[index].sum,tree[index].lazya,tree[index].lazyb);
    return;
  }
  int mid=(i+j)>>1;
  printTree(L(index),i,mid);
  printTree(R(index),mid+1,j);
  printf("%d,%d %lld %lld %lld %lld\n",i,j,tree[index].sqSum,tree[index].sum,tree[index].lazya,tree[index].lazyb);
}

int main(){
  int T;
  scanf("%d",&T);
  for(int tc=0;tc<T;++tc){

    scanf("%d %d",&N,&Q);
    for(int i=0;i<N;++i) scanf("%lld",&A[i]);
    
    build(1,1,N);
    //    cout << "------" << endl;
    //    printTree(1,1,N);
    printf("Case %d:\n",tc+1);    
    for(int i=0;i<Q;++i){
      int ty,u,v;
      scanf("%d %d %d",&ty,&u,&v);
      
      if(ty==0){
	scanf("%lld",&value);
	update0(1,1,N,u,v);
      }
      else if(ty==1){
	scanf("%lld",&value);
	update1(1,1,N,u,v);
      }
      else
	printf("%lld\n",query(1,1,N,u,v));
      //      cout << "------" << endl;
      //      printTree(1,1,N);

    }
   
    
  }
  return 0;
}



