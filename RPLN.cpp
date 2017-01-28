#include <bits/stdc++.h>
#define NMAX 111111
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)

using namespace std;
int tree[NMAX<<2];
int input[NMAX];

void build(int index,int i,int j){
  if(i==j){
    tree[index]=input[i-1];
    return;
  }
  int mid=(i+j)>>1;
  build(L(index),i,mid);
  build(R(index),mid+1,j);
  tree[index]=min(tree[L(index)],tree[R(index)]);
}

int query(int index,int i,int j,int left,int right){
  if(i==left && j==right) return tree[index];
  int mid=(i+j)>>1;
  if(right<=mid) return query(L(index),i,mid,left,right);
  else if(left>mid) return query(R(index),mid+1,j,left,right);
  return min(query(L(index),i,mid,left,mid),query(R(index),mid+1,j,mid+1,right));
}

void print(int index,int i,int j){
  if(i==j){
    cout<<i<<","<<j<<" "<<tree[index]<<endl;
    return;
  }
  int mid=(i+j)>>1;
  print(L(index),i,mid);
  print(R(index),mid+1,j);
  cout<<i<<","<<j<<" "<<tree[index]<<endl;
}

int main(){
  int T;
  //cin>>T;
  scanf("%d",&T);
  for(int t=0;t<T;++t){
    int n,q;
    //cin>>n>>q;
    scanf("%d %d",&n,&q);
    for(int i=0;i<n;++i) scanf("%d",&input[i]);
      //cin>>input[i];
    build(1,1,n);
    printf("Scenario #%d:\n\n",t+1);
    //cout<<"Scenario #"<<t+1<<":\n"<<endl;
    //print(1,1,n);
    for(int i=0;i<q;++i){
      int u,v;
      //cin>>u>>v;
      scanf("%d %d",&u,&v);
      //cout<<query(1,1,n,u,v)<<"\n"<<endl;
      printf("%d\n\n",query(1,1,n,u,v));
    }
  }
  return 0;
}
