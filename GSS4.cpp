// By noob.

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <complex>
#pragma comment(linker, "/STACK:266777216")

using namespace std;

#define assert(f) { if(!(f)) { fprintf(stderr,"Assertion failed: "); fprintf(stderr,#f); fprintf(stderr,"\n"); exit(1); } }

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<double> VD;
typedef pair<double,double> PDD;

const int inf=1000000000;
const LL INF=LL(inf)*inf;
const double eps=1e-9;
const double PI=2*acos(0.0);
#define bit(n) (1<<(n))
#define bit64(n) ((LL(1))<<(n))
#define pb push_back
#define sz size()
#define mp make_pair
#define cl clear()
#define all(a) (a).begin(),(a).end()
#define fill(ar,val) memset((ar),(val),sizeof (ar))
#define MIN(a,b) {if((a)>(b)) (a)=(b);}
#define MAX(a,b) {if((a)<(b)) (a)=(b);}
#define sqr(x) ((x)*(x))
#define X first
#define Y second

clock_t start=clock();

inline LL sq_root(LL x)
{
	if(x==0) return 0;
	LL res=1;

	for( ;res*res<=x;++res);
	return res;
}

#define N 100010

int n;
LL tree[N],parent[N],input[N];

inline void update(int idx,LL val)
{
	for(int i=idx;i<=n;i+=(i&-i))
		tree[i]+=val;
}

inline LL query(int idx)
{
	LL res=0;
	for(int i=idx;i>0;i-=(i&-i))
		res+=tree[i];
	return res;
}

inline LL range_query(int left,int right)
{
	return query(right)-query(left-1);
}

int find(int x)
{
	if(parent[x]!=x) parent[x]=find(parent[x]);
	return parent[x];
}

void modify(int i,int j)
{
	int curr=find(i);
	while(curr>=i && curr<=j)
	{
		if(input[curr]!=1){
			update(curr,-input[curr]);
			input[curr]=(LL)floor(sqrt((double)input[curr]));
			update(curr,input[curr]);
			if(input[curr]==1)	parent[curr]=curr+1;
		}
		curr=find(curr+1);
	}
}

int main()
{
	//freopen("1.in","r",stdin);

	int cs=1;

	while(scanf("%d",&n)==1)
	{
		memset(tree,0,sizeof(tree));
		for(int i=1;i<=n;++i){
			scanf("%lld",&input[i]);
			update(i,input[i]);
			parent[i]=i;
		}
		int m;
		scanf("%d",&m);
		printf("Case #%d:\n",cs);
		++cs;
		for(int i=0;i<m;++i)
		{
			int op,u,v;

			scanf("%d %d %d",&op,&u,&v);
			if(u>v) swap(u,v);
			if(op)	printf("%lld\n",range_query(u,v));
			else modify(u,v);

		}
	}


	return 0;
}
