#include <bits/stdc++.h>
#define NMAX 11111
#define x first
#define y second

using namespace std;
typedef long long int ll;
typedef pair<int,int> pii;

ll tree[NMAX];
inline void add(int idx,ll val){
  for(int i=idx;i<NMAX;i+=(i&-i))
    tree[i]=max(tree[i],val);
}
inline ll get(int idx){
  ll res=-1;
  for(int i=idx;i>0;i-=(i&-i))
    res=max(res,tree[i]);
  return res;
}

pair<pii,ll> r[NMAX];

int main(){
  int t;
  scanf("%d",&t);
  while(t--){
    memset(tree,0,sizeof(tree));
    int N;
    scanf("%d",&N);
    vector<int> tmp;

    for(int i=0;i<N;++i){
      scanf("%d %d %lld",&r[i].x.x,&r[i].x.y,&r[i].y);
      r[i].x.y+=r[i].x.x;
      swap(r[i].x.x,r[i].x.y);
    }
    sort(r,r+N);
    for(int i=0;i<N;++i) tmp.push_back(r[i].x.x);
    for(int i=0;i<N;++i){
      int st=r[i].x.y;
      int pos=upper_bound(tmp.begin(),tmp.end(),st)-tmp.begin()+1;
      //cout << get(pos) << endl;
      add(i+2,get(pos)+r[i].y);
    }
    printf("%lld\n",get(N+3));
  }
  return 0;
}
