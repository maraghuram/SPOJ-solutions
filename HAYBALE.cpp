#include <bits/stdc++.h>
#define NMAX 1111111
using namespace std;

int tree[NMAX];
inline void add(int pos,int val){
  for(int i=pos;i<NMAX;i+=(i&-i))
    tree[i] += val;
}

inline int get(int pos){
  if(pos==0) return 0;
  int res=0;
  for(int i=pos;i>0;i-=(i&-i))
    res += tree[i];
  return res;
}

int main(){
  int n,m;
  scanf("%d %d",&n,&m);

  for(int i=0;i<m;++i){
    int u,v;
    scanf("%d %d",&u,&v);
    if( u>v ) swap(u,v);
    ++u,++v;

    add(u,1);
    add(v+1,-1);
  }

  vector<int> A(n);
  for(int i=0;i<n;++i)
    A[i] = get(i+1);
  sort(A.begin(),A.end());
  printf("%d\n", A[(A.size()-1)/2]);

  return 0;
}
