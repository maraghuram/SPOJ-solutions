#include <cstring>
#include <cstdio>
#include <vector>
#define NMAX 111
#define x first
#define y second
#define pb push_back
#define sz size()

using namespace std;
typedef pair<int,int> pii;

char seq[]="ALLIZZWELL";

char input[NMAX][NMAX];
int visited[NMAX][NMAX];
int M,N;
int flag;

vector<pii> getNeighbours(pii pt){
	vector<pii> res;
	if(pt.x>0) res.pb(pii(pt.x-1,pt.y));
	if(pt.y>0) res.pb(pii(pt.x,pt.y-1));
	if(pt.x<M-1) res.pb(pii(pt.x+1,pt.y));
	if(pt.y<N-1) res.pb(pii(pt.x,pt.y+1));
	if(pt.x>0 && pt.y>0) res.pb(pii(pt.x-1,pt.y-1));
	if(pt.x>0 && pt.y<N-1) res.pb(pii(pt.x-1,pt.y+1));
	if(pt.x<M-1 && pt.y>0) res.pb(pii(pt.x+1,pt.y-1));
	if(pt.x<M-1 && pt.y<N-1) res.pb(pii(pt.x+1,pt.y+1));
	return res;
}

void dfs(pii pt,int depth){
	//printf("%d,%d - %d\n",pt.x,pt.y,depth);
	if(depth==9) {
		flag=1;
		return;
	}
	visited[pt.x][pt.y]=1;
	vector<pii> adj=getNeighbours(pt);
	for(int i=0;i<adj.sz;++i){
		pii v=adj[i];
		if(!visited[v.x][v.y] && input[v.x][v.y]==seq[depth+1]){
			dfs(v,depth+1);
			visited[v.x][v.y]=0;
		}
	}
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&M,&N);
		for(int i=0;i<M;++i) scanf("%s",input[i]);
		/*for(int i=0;i<M;++i){
			printf("\n");
			for(int j=0;j<N;++j) printf("%c ",input[i][j]);
		}*/
		flag=0;
		memset(visited,0,sizeof(visited));
		for(int i=0;i<M;++i)
			for(int j=0;j<N;++j)
				if(input[i][j]=='A') dfs(pii(i,j),0);
		if(flag==1) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}
