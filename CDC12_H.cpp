#include <bits/stdc++.h>
#define NMAX 111111
#define L(x) ( x<<1 )
#define R(x) ( ( x<<1 ) + 1 )
using namespace std;

typedef long long int ll;

ll lazy[NMAX<<2],sum[NMAX<<2];

void update(int index,int i,int j,int left,int right){
  if( lazy[index] ){
    sum[index] += (lazy[index]*(j-i+1));
    if( i!=j ) {
      lazy[L(index)] += lazy[index];
      lazy[R(index)] += lazy[index];
    }
    lazy[index] = 0;
  }

  if( left<=i  && j<= right ) {
    sum[index] += (j-i+1);
    if( i!=j ){
      lazy[L(index)] += 1;
      lazy[R(index)] += 1;
    }   
    return;
  } 

  if( i>right || j<left) return;

  int mid = ( i + j ) >> 1;
  update( L(index), i, mid, left, right );
  update( R(index), mid + 1, j, left, right );
  
  sum[index] = sum[L(index)] + sum[R(index)];    
}

ll query(int index,int i,int j, int left, int right ){
  if( lazy[index] ){
    sum[index] += (lazy[index]*(j-i+1));
    if( i!=j ) {
      lazy[L(index)] += lazy[index];
      lazy[R(index)] += lazy[index];
    }
    lazy[index] = 0;
  }

  if( left<=i  && j<= right ) return sum[index];
  if( i>right || j<left) return 0;

  int mid = ( i + j ) >> 1;
  ll res1 = query( L(index), i, mid, left, right );
  ll res2 = query( R(index), mid + 1, j, left, right);
  
  sum[index] = sum[L(index)] + sum[R(index)];    
  return ( res1 + res2 );
}

void printTree(int index,int i,int j){
  if( i==j ) {
    cout<< i<<","<<j<<" "<<sum[index]<<" "<<lazy[index]<<endl;
    return;
  }
  int mid=(i+j)>>1;
  printTree(L(index),i,mid);
  printTree(R(index),mid+1,j);
  cout<< i<<","<<j<<" "<<sum[index]<<" "<<lazy[index]<<endl;
	      
}

int main(){
  int T;
  scanf("%d",&T);
  for(int k = 0; k<T; ++k) {
    memset(lazy,0,sizeof(lazy));
    memset(sum,0,sizeof(sum));
    printf("Scenario #%d:\n", k + 1 );
    int N,Q;
    scanf( "%d %d", &N, &Q );
    for(int i=0; i<Q; ++i){
      int x,y;
      char str[20];
      scanf("%s %d %d",str,&x,&y);
      if( str[0]=='a' ) printf("%lld\n", query(1,1,N,x,y));
      else {
	printf("OK\n");
	update(1,1,N,x,y);
	//cout<<"_____> "<<endl;
	//	printTree(1,1,N);
      }
    }
  }
  return 0;
}
