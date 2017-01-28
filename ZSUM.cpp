#include <bits/stdc++.h>
#define MOD 10000007
using namespace std;
typedef long long int ll;

ll powmod(ll base,ll exp){
  ll res=1;
  while(exp>0){
    if(exp&1) res=(res*base)%MOD;
    base=(base*base)%MOD;
    exp>>=1;
  }
  return res;
}

int main(){
  while(1){
    ll n,k,res=0;
    scanf("%lld %lld",&n,&k);
    if( n==0 && k==0) break;
    res += powmod(n,k);
    res %= MOD;
    res += ((2*powmod(n-1,k))%MOD);
    res %= MOD;
    res += powmod(n,n);
    res %= MOD;
    res += ((2*powmod(n-1,n-1))%MOD);
    res %= MOD;
    printf("%lld\n",res);
  }
  return 0;
}
