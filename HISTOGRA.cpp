#include <bits/stdc++.h>
#define NMAX 111111
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)

using namespace std;
typedef long long int ll;

ll height[NMAX];
int N;

struct node{
  ll minH;
  ll ind;
  node(){
    minH=NMAX;
  }
  node(ll x){
    minH=x;
  }
}tree[NMAX<<2];

void merge(node &z,node x,node y){
  z=node(min(x.minH,y.minH));
  if( x.minH<y.minH ) z.ind=x.ind;
  else z.ind=y.ind;
}

void build(int index,int i,int j){
  if(i==j){
    tree[index].minH=height[i-1];
    tree[index].ind=i;
    return;
  }

  int mid=(i+j)>>1;
  build(L(index),i,mid);
  build(R(index),mid+1,j);

  merge(tree[index],tree[L(index)],tree[R(index)]);
}

node query(int index,int i,int j,int left,int right){
  if(i==left && j==right) return tree[index];
  int mid=(i+j)>>1;
  if(right<=mid) return query(L(index),i,mid,left,right);
  else if(left>mid) return query(R(index),mid+1,j,left,right);
  else{
    node x,y,z;
    x=query(L(index),i,mid,left,mid);
    y=query(R(index),mid+1,j,mid+1,right);
    merge(z,x,y);
    return z;
  }
}

ll solve(int left,int right){

  if(left==right) return height[left-1];
  if(left>right) return 0;
  int m=query(1,1,N,left,right).ind;
  //  cout<<left<<" "<<right<<" "<<m<<endl;
  return max(max(solve(left,m-1),solve(m+1,right)),(right-left+1)*height[m-1]);
}

// void print(int index,int i,int j){
//   if(i==j) {
//     cout<<i<<","<<j<<" ";
//     cout<<tree[index].minH<<" "<<tree[index].area<<" "<<tree[index].width<<endl;
//     return;
//   }
//   int mid=(i+j)>>1;
//   print(L(index),i,mid);
//   print(R(index),mid+1,j);
//   cout<<i<<","<<j<<" ";
//   cout<<tree[index].minH<<" "<<tree[index].area<<" "<<tree[index].width<<endl;
// }

int main(){
  while(1){    
    scanf("%d",&N);
    if(N==0) break;
    memset(height,0,sizeof(height));
    for(int i=0;i<N;++i) scanf("%lld",&height[i]);
    build(1,1,N);
    //print(1,1,N);
    printf("%lld\n",solve(1,N));
  }

  return 0;
}
