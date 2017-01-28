#include <bits/stdc++.h>
#define NMAX 111111
#define DMAX 27
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)
typedef long long int ll;

using namespace std;
int N,M;
ll A[NMAX];

struct node{
  int onCnt[DMAX];
  node(){
    for(int i=0;i<DMAX;++i){
      onCnt[i]=0;
    }
  }
}tree[NMAX<<2];

inline void modify(int index,ll val){
  for(int i=0,j=1;i<DMAX;++i,j<<=1){
    tree[index].onCnt[i]=j&val?1:0;
  }
}

void merge(node x,node y,node &z){
  for(int i=0;i<DMAX;++i){
    z.onCnt[i] = x.onCnt[i]+y.onCnt[i];
  }
}

void build(int index,int i,int j){
  tree[index]=node();
  if(i==j){
    modify(index,A[i-1]);
    return;
  }
  int mid=(i+j)>>1;
  build(L(index),i,mid);
  build(R(index),mid+1,j);
  merge(tree[L(index)],tree[R(index)],tree[index]);
}

void update(int index,int i,int j,int pos,ll val){
  if(i==j && i==pos){
    modify(index,val);
    return;
  }
  int mid=(i+j)>>1;
  if(pos<=mid) update(L(index),i,mid,pos,val);
  else update(R(index),mid+1,j,pos,val);
  merge(tree[L(index)],tree[R(index)],tree[index]);  
}

node query(int index,int i,int j,int st,int en){
  if(i==st && j==en) return tree[index];
  int mid=(i+j)>>1;
  if(en<=mid) return query(L(index),i,mid,st,en);
  else if(st>mid) return query(R(index),mid+1,j,st,en);
  else{
    node tmp=node();  
    merge(query(L(index),i,mid,st,mid),query(R(index),mid+1,j,mid+1,en),tmp);
    return tmp;
  }
}


int main(){
  char buf[5];
  int ty,u,v;

  scanf("%d %d",&N,&M);
  for(int i=0;i<N;++i){
    scanf("%lld",&A[i]);
    assert(A[i]<=100000000 && A[i]>=0);
  }
  build(1,1,N);
  for(int i=0;i<M;++i){
    scanf("%d",&ty);
    if(ty==1){
      scanf("%d %d",&u,&v);
      update(1,1,N,v,u);
    }
    else{
      node res;
      ll ans,sz,on,off,tot;
      ans=0;

      scanf("%s %d %d",buf,&u,&v);
      //assert(u!=v);
      if(u==v) printf("0\n");
      else{
	res=query(1,1,N,u,v);
	sz=v-u+1;
	if(buf[0]=='X'){
	  for(int i=0;i<DMAX;++i){
	    on=res.onCnt[i];
	    ans += (on*(sz-on)*(1<<i));
	  }
	}
	else if(buf[0]=='O'){
	  for(int i=0;i<DMAX;++i){
	    on=res.onCnt[i];
	    off=sz-on;
	    tot=(sz*(sz-1))/2;
	    ans += (tot-((off*(off-1))/2))*(1<<i);
	  }

	}
	else{
	  for(int i=0;i<DMAX;++i){
	    on=res.onCnt[i];
	    ans += ((on*(on-1))*(1<<i))/2;
	  }
	}
	
	printf("%lld\n",ans);
      }
    }
  }

  return 0;
}
