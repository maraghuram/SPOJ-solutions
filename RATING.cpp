// By noob.

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <climits>
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

#define NMAX 333333
#define RMAX 111111

struct student
{
	int Open,High;
	int pos;
};

int tree[RMAX],result[NMAX];
student input[NMAX];

bool comp(const student x,const student y)
{
	if(x.High==y.High) return x.Open < y.Open;
	return x.High < y.High;
}

void update(int idx,int val){
    for(int x = idx;x <= 100000;x += x & -x)
        tree[x]+=val;
}

int read(int idx){
    int ret = 0;

    for(int x = idx;x > 0;x -= x & -x)
        ret += tree[x];

    return ret;
}

int main()
{
	memset(tree,0,sizeof(tree));
	memset(result,0,sizeof(result));
	int n,e;
	scanf("%d",&n);

	for(int i=0;i<n;++i){
		scanf("%d %d",&input[i].Open,&input[i].High);
		input[i].pos=i;
	}

	sort(input,input+n,comp);

	for(int i=0;i<n;){
		int e=i;
		while(e<n && input[e].High==input[i].High && input[e].Open==input[i].Open) ++e;

		for(int j=i;j<e;++j) result[input[j].pos]=read(input[j].Open);
		for(int j=i;j<e;++j) update(input[j].Open,1);

		i=e;
		//if(i!=n-1 && input[i].High==input[i+1].High && input[i].Open==input[i+1].Open)
			//result[input[i].pos]=1;
		//result[input[i].pos]+=read(input[i].Open);
		//update(input[i].Open,1);
		//printf("\n%d %d",i,e);
	}

	for(int i=0;i<n;++i) printf("%d\n",result[i]);

	return 0;
}


