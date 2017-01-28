#include <bits/stdc++.h>
#define NMAX 111111
using namespace std;
typedef long long int ll;

ll tree[NMAX];

inline void update( int index, ll val ){
  for(int i=index;i<NMAX;i+=(i&-i))
    tree[i]+=val;
}
inline ll query( int index ){
  ll res=0;
  for(int i=index;i>0;i-=(i&-i)) 
    res += tree[i];
  return res;
}

int main(){
  int T;
  scanf("%d",&T);
  while(T--){
    memset(tree,0,sizeof(tree));
    int n,u;
    scanf("%d %d",&n,&u);
    for(int i=0;i<u;++i){
      int l,r;
      ll val;
      scanf("%d %d %lld",&l,&r,&val);
      ++l,++r;
      update(l,val);
      update(r+1,-val);
    }
    int q;
    scanf("%d",&q);
    for(int i=0;i<q;++i){
      int pt;
      scanf("%d",&pt);
      ++pt;
      printf("%lld\n",query(pt));
    }
      
  }

  return 0;
}
