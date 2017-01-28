#include <bits/stdc++.h>
#define inf 99999999
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;

int main(){
  int T;
  scanf("%d",&T);
  while(T--){
    vector<pii> coins;
    vector<int> dp;
    int E,F;
    scanf("%d %d",&E,&F);
    int N;
    scanf("%d",&N);
    dp=vector<int>(F+1,inf);

    for(int i=0;i<N;++i) {
      int p,w;
      scanf("%d %d",&p,&w);
      coins.push_back(pii(p,w));
      dp[w]=p;
    }

    dp[0]=0;
    for(int i=1;i<=(F-E);++i){
	int best,curr;
	best=inf;
	for(int j=0;j<N;++j){
	  curr=inf;
	  if(i-coins[j].y>=0){
	    if(dp[i-coins[j].y]!=inf)
	      curr=dp[i-coins[j].y]+coins[j].x;
	  }
	  best=min(best,curr);
	}
	dp[i]=best;
    }

    if(dp[F-E]==inf) printf("This is impossible.");
    else printf("The minimum amount of money in the piggy-bank is %d.",dp[F-E]);

    if(T) printf("\n");
  }

  return 0;
}