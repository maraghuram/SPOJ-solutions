#include <bits/stdc++.h>
using namespace std;

int main(){
  int T;
  scanf("%d",&T);
  while(T--){
    int N;
    long long int P;
    scanf("%d %lld",&N,&P);
 
    vector<long long int> A(N);
    for(int i=0;i<N;++i) scanf("%lld",&A[i]);

    sort(A.begin(),A.end());
    long long int sum = 0;
    int cnt=0;
    for(int i=0;i<N;++i)
      if( A[i]+sum <= P ) sum+=A[i],++cnt;

    printf("%d\n",cnt);
  }
  return 0;

}
