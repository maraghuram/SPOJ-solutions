#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int a[100010], N;
int b[100010], K;
int inc[100010], dec[100010];

int main()
{
for (int cs = 1; cs <= 10 && scanf("%d", &N) == 1 && N > 0; cs++) {
for (int i = 0; i < N; i++)
scanf("%d", &a[i]);

K = 0;
for (int i = 0; i < N; i++) {
int left = -1, right = K;
while (right - left > 1) {
int mid = (left + right) / 2;
if (b[mid] > a[i])
right = mid;
else
left = mid;
}
inc[i] = right+1;
b[right] = a[i];
if (right == K) K++;
}

K = 0;
for (int i = N-1; i >= 0; i--) {
int left = -1, right = K;
while (right - left > 1) {
int mid = (left + right) / 2;
if (b[mid] < a[i])
right = mid;
else
left = mid;
}
dec[i] = right+1;
b[right] = a[i];
if (right == K) K++;
}

//printf(" a="); for (int i = 0; i < N; i++) printf(" %d", a[i]); printf("\n");
//printf("inc="); for (int i = 0; i < N; i++) printf(" %d", inc[i]); printf("\n");
//printf("dec="); for (int i = 0; i < N; i++) printf(" %d", dec[i]); printf("\n");

int len = inc[0];
for (int i = 0; i < N; i++)
if (inc[i] > len) len = inc[i];

vector<int> out;
for (int i = 0; i < N; i++)
if (inc[i] + dec[i] - 1 == len)
out.push_back(a[i]);

sort(out.begin(), out.end());

printf("%d\n", out.size());
for (int i = 0; i < (int)out.size(); i++)
printf(i == 0 ? "%d" : " %d", out[i]);
printf("\n");
}
return 0;
}input,input+N);
    for(int i=N-1;i>=0;--i){
      decr[input[i]]=query(1,1,N,input[i]+1,N)+1;
      update(1,1,N,input[i],decr[input[i]]);
    }
    vector<int> res;
    for(int i=0;i<N;++i)
      if(inc[input[i]]+decr[input[i]]-1==best) res.push_back(input[i]);
    sort(res.begin(),res.end());
    printf("%d\n",res.size());
    for(int i=0;i<res.size();++i) printf(i==0?"%d":" %d",res[i]);
    //printf("%d\n",res[res.size()-1]);    
    printf("\n");
  /*
  vector<int> res2;
  for(int n = 0 ; n < N ; n++){
       lis[n] = 1;
	   for(int h = 0 ; h < n ; h++)
		   if(input[n] > input[h])
			   lis[n] = max(lis[n] , lis[h] + 1);
      if(lis[n]==best) res2.push_back(input[n]);
   }
  printf("%d\n",res2.size()) ;
  assert(res.size()==res2.size());
  for(int i=0;i<res.size();++i) assert(res[i]==res2[i]);*/
  }
  return 0;
}

