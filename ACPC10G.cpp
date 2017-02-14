#include <bits/stdc++.h>
#define NMAX 16
using namespace std;

typedef long long int ll;

int points[NMAX][2], knights[NMAX][2];
int n;

ll dp[NMAX][1<<(NMAX+1)],knightDistances[NMAX][NMAX];
vector<int> subsetMasks[NMAX];

inline ll knightDistance(ll x1, ll y1, ll x2, ll y2)
{
	ll dx = abs(x2-x1);
	ll dy = abs(y2-y1);
	ll lb=(dx+1)/2;
	lb = max(lb, (dy+1)/2);
	lb = max(lb, (dx+dy+2)/3);
	while ((lb%2)!=(dx+dy)%2) lb++;
	if (abs(dx)==1 && dy==0) return 3;
	if (abs(dy)==1 && dx==0) return 3;
	if (abs(dx)==2 && abs(dy)==2) return 4;
	return lb;
}

void computeDistances(){
  for(int i=1;i<=n;++i){
    for(int j=1;j<=n;++j){
      knightDistances[i][j] = knightDistance(knights[i-1][0], knights[i-1][1], points[j-1][0], points[j-1][1]);
      //cout << knightDistances[i][j] << " ";
    }
    //cout << endl;
  }
}

ll solve(){
  dp[0][0] = 0;
  computeDistances();

  int maxSubs = 1 << n;

  for(int i=1;i<=n;++i){
    for(int j=0;j<subsetMasks[i].size();++j){
      int mask = subsetMasks[i][j];
      if(mask>=maxSubs) continue;

      dp[i][mask] = LLONG_MAX;
      for(int testBit=1, cnt=1;testBit<=mask; testBit <<= 1, ++cnt){
	if(mask & testBit){
	  int prevMask = mask & (~testBit);
	  //cout << bitset<32>(mask) << " " << bitset<32>(prevMask) << " " << dp[i-1][prevMask] << endl;
	  dp[i][mask] = min(dp[i][mask], knightDistances[i][cnt] + dp[i-1][prevMask]);
	}
      }

    }
  }

  for(int i=0;i<subsetMasks[n].size();++i)
    if(subsetMasks[n][i] < maxSubs)
      return dp[n][subsetMasks[n][i]];

  assert(false);
}


int main(){
  ios::sync_with_stdio(false);

  for(int i=1;i<(1<<NMAX); ++i)
    subsetMasks[__builtin_popcount(i)].push_back(i);

  int ts = 1;

  while(1){
    cin >> n;

    if(n == 0) break;

    for(int i=0;i<n;++i)
      cin >> knights[i][0] >> knights[i][1];

    for(int i=0;i<n;++i)
      cin >> points[i][0] >> points[i][1];

    cout << ts << ". " << solve() << endl;

    ++ts;
  }


  return 0;
}
