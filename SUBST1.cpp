#include <bits/stdc++.h>
#define NMAX 50010
#define getc getchar_unlocked
using namespace std;
typedef long long int ll;
// struct node{
//   int idx;
//   int rank,nxt;
// }suf[NMAX];

// bool cmp(const node &x,const node &y){
//   if(x.rank==y.rank) return x.nxt<y.nxt;
//   return x.rank<y.rank;
// }

// int cmp2(const void *a,const void *b){
//   node x=*reinterpret_cast<const node*>(a);
//   node y=*reinterpret_cast<const node*>(b);
//   if(x.rank==y.rank && x.nxt==y.nxt) return 0;
//   if(x.rank==y.rank) return x.nxt<y.nxt?-1:1;
//   return x.rank<y.rank?-1:1;  
// }

// int N;
// int lcp[NMAX],tmp[NMAX];
// char str[NMAX];

// // void SuffixSort(){
// //   for(int i=0;i<N;++i){
// //     suf[i].idx=i;
// //     suf[i].rank=str[i]-'A';
// //     suf[i].nxt=i+1<N?str[i+1]-'A':-1;
// //   }
// //   sort(suf,suf+N,cmp);
// //   for(int l=2;l<(N<<2);l<<=1){
// //     int rank=0;
// //     int prev=suf[0].rank;
// //     suf[0].rank=0;
// //     ind[suf[0].idx]=0;
    
// //     for(int i=1;i<N;++i){
// //       if(suf[i].rank==prev && suf[i].nxt==suf[i-1].nxt){
// // 	prev=suf[i].rank;
// // 	suf[i].rank=rank;
// //       }
// //       else{
// // 	prev=suf[i].rank;
// // 	suf[i].rank=++rank;
// //       }
// //       ind[suf[i].idx]=i;
// //     }
// //     for(int i=0;i<N;++i){
// //       int cur=suf[i].idx+l;
// //       suf[i].nxt=cur<N?suf[ind[cur]].rank:-1;
// //     }
// //     sort(suf,suf+N,cmp);
// //   }
// //   for(int i=0;i<N;++i)
// //     //cout << string(str).substr(suf[i].idx,N-suf[i].idx) << endl;
// //     cout << suf[i].idx << endl;
// // }

// void SuffixSort2(){
//   for(int i=0;i<N;++i) tmp[i]=str[i]-'A';
//   for(int l=1;l>>1<N;l<<=1){
//     for(int i=0;i<N;++i){
//       suf[i].idx=i;
//       suf[i].rank=tmp[i];
//       suf[i].nxt=i+l<N?tmp[i+l]:-1;
//     }
//     sort(suf,suf+N,cmp);
//     for(int i=0;i<N;++i)
//       tmp[suf[i].idx]=i>0 && suf[i].rank==suf[i-1].rank && suf[i].nxt==suf[i-1].nxt?tmp[suf[i-1].idx]:i;
//   }
//   // for(int i=0;i<N;++i)
//   //   //cout << string(str).substr(suf[i].idx,N-suf[i].idx) << endl;
//   //   cout << suf[i].idx << endl;

// }

// void Lcp(){
//   lcp[suf[0].idx]=0;
//   for(int i=0,h=0;i<N;++i){
//     if(tmp[i]>0){
//       int j=suf[tmp[i]-1].idx;
//       while(i+h<N && j+h<N && str[i+h]==str[j+h]) ++h;
//       lcp[i]=h;
//       if(h>0) --h;
//     }
//   }
// }

// void solve(){
//   long long res=0;
//   for(int i=0;i<N;++i)
//     res += N-i-lcp[i];
//   printf("%lld\n",res);
// }

// inline void readStr(char *buf){
//   int i=0;
//   char c;
//   while(1){
//     c=getc();
//     if(c>='A' && c<='Z')
//       buf[i++]=c;
//     else break;
//   }
//   buf[i]='\0';
// }

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
  dist[0]=N-pos[0];
  for(int i=1;i<N;++i) dist[i] = dist[i-1]+(N-pos[i]-lcp[pos[i]]);
}


int main(){
  int t;
  scanf("%d\n",&t);
  while(t--){
    //scanf("%s",str);
    gets(str);
    //readStr(str);
    N=0;
    for(int i=0;str[i]!='\0';++i)++N;
    suffixSort(N);
    Lcp();
    printf("%lld\n",dist[N-1]);
  }
  return 0;
}
