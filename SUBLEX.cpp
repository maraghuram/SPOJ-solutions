#include <bits/stdc++.h>
#define NMAX 90010
#define getc getchar_unlocked
using namespace std;
typedef long long int ll;

int N;
int lcp[NMAX];
char str[NMAX];
string a;
ll dist[NMAX];
 
int rank[NMAX], pos[NMAX];
int cnt[NMAX], next[NMAX];
bool bh[NMAX], b2h[NMAX];
 
bool smaller_first_char(int a, int b){
  return str[a] < str[b];
}



void suffixSort(int n){
  for (int i=0; i<n; ++i){
    pos[i] = i;
  }
  sort(pos, pos + n, smaller_first_char);
 
  for (int i=0; i<n; ++i){
    bh[i] = i == 0 || str[pos[i]] != str[pos[i-1]];
    b2h[i] = false;
  }
 
  for (int h = 1; h < n; h <<= 1){
    int buckets = 0;
    for (int i=0, j; i < n; i = j){
      j = i + 1;
      while (j < n && !bh[j]) j++;
      next[i] = j;
      buckets++;
    }
    if (buckets == n) break;
    for (int i = 0; i < n; i = next[i]){
      cnt[i] = 0;
      for (int j = i; j < next[i]; ++j){
        rank[pos[j]] = i;
      }
    }
 
    cnt[rank[n - h]]++;
    b2h[rank[n - h]] = true;
    for (int i = 0; i < n; i = next[i]){
      for (int j = i; j < next[i]; ++j){
        int s = pos[j] - h;
        if (s >= 0){
          int head = rank[s];
          rank[s] = head + cnt[head]++;
          b2h[rank[s]] = true;
        }
      }
      for (int j = i; j < next[i]; ++j){
        int s = pos[j] - h;
        if (s >= 0 && b2h[rank[s]]){
          for (int k = rank[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
        }
      }
    }
    for (int i=0; i<n; ++i){
      pos[rank[i]] = i;
      bh[i] |= b2h[i];
    }
  }
  for (int i=0; i<n; ++i){
    rank[pos[i]] = i;
  }
}

void Lcp(){
  lcp[pos[0]]=0;
  for(int i=0,h=0;i<N;++i){
    if(rank[i]>0){
      int j=pos[rank[i]-1];
      while(i+h<N && j+h<N && str[i+h]==str[j+h]) ++h;
      lcp[i]=h;
      if(h>0) --h;
    }
  }
  cnt[0]=N-pos[0];
  for(int i=1;i<N;++i) cnt[i] = cnt[i-1]+(N-pos[i]-lcp[pos[i]]);
}

void solve(){
  int Q;
  ll p;
  scanf("%d",&Q);
  for(int i=0;i<Q;++i){    
    scanf("%lld",&p);
    int t=lower_bound(cnt,cnt+N,p)-cnt;
    int tmp=t>0?cnt[t-1]:0;
    puts(a.substr(pos[t],lcp[pos[t]]+p-tmp).c_str());
  }
}

int main(){
  int t;
  gets(str);
  a=string(str);
  N=0;
  for(int i=0;str[i]!='\0';++i)++N;
  suffixSort(N);
  Lcp();
  solve();
  return 0;
}
