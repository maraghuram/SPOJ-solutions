#include <iostream>
#include <cstdio>
 
using namespace std;
 
int dp[26][35],input[26];
int N,F,H,S,MAX_EMP;
 
const int INT_MAX=1000000000;
const int INT_MIN=-1;
 
void DoDynamicProgramming()
{
for(int i=1;i<=N;++i)
for(int j=0;j<=MAX_EMP;++j)
dp[i][j]=INT_MAX;
 
for(int j=input[0];j<=MAX_EMP;++j)	
dp[1][j]=(H+S)*j;
 
for(int i=2;i<=N;++i)
for(int j=input[i-1];j<=MAX_EMP;++j)
{
if(input[i-1]>j) continue;
for(int k=0;k<=MAX_EMP;++k)
dp[i][j]=min(dp[i][j],dp[i-1][k]+S*j+(j<k?(k-j)*F:(j-k)*H));
 
}
 
}
 
/*void DoDynamicProgramming()
{
  // Fill all disallowed entries with infinity
  for (int i = 0; i < input[0]; ++i)
  dp[0][i] = 1000000000;
  for(int i = input[0]; i <= MAX_EMP; i++) //for num workers in 1st month
  dp[0][i] = i*(H + S);
 
  for(int i = 1; i < N; i++)
  for(int j = 0; j <= MAX_EMP; j++)
  {
  // No need for special case handling,
  //just check all previous numbers of employees
  dp[i][j] = 1000000000;
  if (input[i] > j) continue;
  for(int k = 0; k <= MAX_EMP; k++)
  dp[i][j] = min(dp[i][j],
  dp[i-1][k] + j*S + (j>k ? (j-k)*H : (k-j)*F));
  }
}
*/
int main()
{
int T=1;
int ans;
 
while(1)
{
MAX_EMP=INT_MIN;
ans=INT_MAX;
 
scanf("%d",&N);
if(N==0) break;
 
scanf("%d %d %d",&H,&S,&F);
for(int i=0;i<N;++i)
{
scanf("%d",&input[i]);
MAX_EMP=max(MAX_EMP,input[i]);
}
 
DoDynamicProgramming();
 
for(int j=0;j<=MAX_EMP;++j)
ans=min(ans,dp[N][j]);
 
printf("Case %d, cost = $%d\n",T,ans);	
 
++T;
}
 
return 0;
}