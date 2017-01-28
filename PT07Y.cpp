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

#define NMAX 11111

vector<int> Graph[NMAX];
int visited[NMAX],parent[NMAX];
int N,M,flag;

void dfs(int u,int p){

	parent[u]=p;
	visited[u]=1;
	for(int i=0;i<Graph[u].sz;++i){
		int v=Graph[u][i];
		if(v==parent[u]) continue;

		if(visited[v]) {
			flag=1;
			return;
		}
		else{
			dfs(v,u);
		}
	}
}

void solve(){
	memset(visited,0,sizeof(visited));
	flag=0;
	dfs(1,-1);
	for(int i=1;i<=N;++i)
		if(!visited[i])
		{
			flag=1;
			break;
		}

	if(flag) printf("NO");
	else printf("YES");
}

int main(){
	scanf("%d %d",&N,&M);
	for(int i=0;i<M;++i){
		int u,v;
		scanf("%d %d",&u,&v);
		Graph[u].pb(v);
		Graph[v].pb(u);
	}

	if(M!=N-1) printf("NO");
	else solve();

	return 0;
}
