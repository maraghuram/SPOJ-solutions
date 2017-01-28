#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef pair< int,int > pii;
int main(){
  int t;
  scanf("%d",&t);
  for(int tc=0;tc<t;++tc){
    int n;
    vector< pii > ranges;
    scanf("%d",&n);

    for(int i=0;i<n;++i){
      int u,v;
      scanf("%d %d",&u,&v);
      ranges.push_back(pii(u,0));
      ranges.push_back(pii(v,1));
    }
    sort(ranges.begin(),ranges.end());

    int res=0,curr=0;
    for(int i=0;i<ranges.size();++i){
      if(ranges[i].second==0) ++curr;
      else --curr;
      res=max(curr,res);
    }
    printf("%d\n",res);
  }
  return 0;
}


