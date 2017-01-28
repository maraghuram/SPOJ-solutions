#include <bits/stdc++.h>
#define NMAX 22222
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)

using namespace std;

int tree[NMAX<<2],input[NMAX],result[NMAX];
int N,K;

void init(int index,int i,int j){
  if( i==j ) {
    tree[index] = input[i];
    return;
  }
  int mid=(i+j)>>1;
  init(L(index),i,mid);
  init(R(index),mid+1,j);

  tree[index] = tree[L(index)] & tree[R(index)];
}

int query(int index,int i,int j,int left,int right){
  if( i==left && j==right )
    return tree[index];

  int mid=(i+j)>>1;

  if(right<=mid ) return query(L(index),i,mid,left,right);
  else if(left>mid) return query(R(index),mid+1,j,left,right);
  else{
    int res = query(L(index),i,mid,left,mid);
    res = res & query(R(index),mid+1,j,mid+1,right);
    return res;
  }
}

void solve(){
  K = min(K,N-1);
  init(1,0,N-1);

  for(int i=0;i<N;++i){
    int res = input[i];

    if( i-K < 0 ){
      res &= query( 1, 0, N-1, 0, i );
      res &= query( 1, 0, N-1, N-K+i, N-1 );
    }
    else
      res &= query( 1, 0, N-1, i-K, i );

    if( i+K > N-1 ){
      res &= query( 1, 0, N-1, i, N-1 );
      res &= query( 1, 0, N-1, 0, i+K-N );
    }
    else
      res &= query( 1, 0, N-1, i, i+K );

    result[i]=res;
  }

  for(int i=0;i<N-1;++i) printf("%d ",result[i]);
  printf("%d\n",result[N-1]);
}

int main(){

  int T;
  scanf("%d",&T);
  while(T--){
    scanf("%d %d",&N,&K);
    for(int i=0;i<N;++i) scanf("%d",&input[i]);
    solve();
  }
  
  return 0;
}
