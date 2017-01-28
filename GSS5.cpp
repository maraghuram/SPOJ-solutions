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

#define NMAX 10100
#define TMAX 1<<18
#define L(X) X<<1
#define R(X) (X<<1) +1

struct node
{
	int best;
	int leftBest,rightBest;
	int sum;
	node(){}
	node(const int a) : best(a),leftBest(a),rightBest(a),sum(a){}
	void merge(node x,node y)
	{
		best=max(x.rightBest+y.leftBest,max(x.best,y.best));
		leftBest=max(x.leftBest,x.sum+y.leftBest);
		rightBest=max(x.rightBest+y.sum,y.rightBest);
		sum=x.sum+y.sum;
	}
};

node tree[TMAX];
int input[NMAX],N;

void build(int index,int i,int j)
{
	if(i==j) {
		tree[index]=node(input[i-1]);
		return;
	}
	int mid=(i+j)>>1;

	build(L(index),i,mid);
	build(R(index),mid+1,j);
	tree[index].merge(tree[L(index)],tree[R(index)]);
}

node query(int index,int i,int j,int left,int right)
{
	if(i==left && j==right) return tree[index];

	int mid=(i+j)>>1;

	if(right<=mid) return query(L(index),i,mid,left,right);
	else if(left>mid) return query(R(index),mid+1,j,left,right);
	else{
		node q1,q2,res;
		q1 = query(L(index),i,mid,left,mid);
		q2 = query(R(index),mid+1,j,mid+1,right);
		res.merge(q1,q2);
		return res;
	}
}

node query(int left,int right)
{

	if(left>right) return node(0);
	return query(1,1,N,left,right);
}

int Query(int x1,int y1,int x2,int y2)
{
	if(x1>x2) swap(x1,x2),swap(y1,y2);

	int res=INT_MIN;

	if(y1<x2)
	{
		int midsum=query(y1+1,x2-1).sum;
		res=query(x1,y1).rightBest+midsum+query(x2,y2).leftBest;
	}
	else
	{
		res=max(query(x1,x2-1).rightBest+query(x2,y2).leftBest,max(query(x1,y1).rightBest+query(y1+1,y2).leftBest,query(x2,y1).best));
	}

	return res;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T>0)
	{
		scanf("%d",&N);
		for(int i=0;i<N;++i) scanf("%d",&input[i]);
		build(1,1,N);
		int M;
		scanf("%d",&M);
		for(int i=0;i<M;++i)
		{
			int x1,y1,x2,y2;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			printf("%d\n",Query(x1,y1,x2,y2));
		}

		--T;
	}
	return 0;
}
