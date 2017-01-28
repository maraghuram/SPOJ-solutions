#include <bits/stdc++.h>
using namespace std;
int main(){
  int t;
  scanf("%d",&t);
  while(t--){
    int N,curr=5;
    int res=0;
    
    scanf("%d",&N);
    
    while(curr<=N){
      res += (N/curr);
      curr=curr*5;
    }
    
    printf("%d\n",res);
  } 
  return 0;
}
