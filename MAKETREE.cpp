#include <bits/stdc++.h>
#define NMAX 100011
#define gc getchar_unlocked
inline void readInt(int &x) {
    register int c = gc();
    x = 0;
    for(; ((c<48 || c>57) && c != '-'); c = gc());

    for(; c>47 && c<58 ; c = gc()) {
    	x = (x<<1) + (x<<3) + c - 48;
    }
}



using namespace std;
vector<int> adj[NMAX];
int outDeg[NMAX],pos[NMAX],s[NMAX],cnt;
int N,K;
queue<int> q;

int main(){
	//scanf("%d %d",&N,&K);
	readInt(N);
	readInt(K);
	cnt=1;
	for(int i=1;i<=K;++i){
		int x,u;
		//scanf("%d",&x);
		readInt(x);
		outDeg[i]=x;
		for(int j=0;j<x;++j){
			//scanf("%d",&u);
			readInt(u);
			adj[u].push_back(i);
		}
	}

	for(int i=1;i<=N;++i)
		if(outDeg[i]==0) q.push(i);
	cnt=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		s[cnt++]=u;
		pos[u]=cnt-1;
		for(int i=0;i<adj[u].size();++i){
			int v=adj[u][i];
			outDeg[v]--;
			if(outDeg[v]==0) q.push(v);
		}
	}

	s[cnt]=0;
	for(int i=1;i<=N;++i) printf("%d\n",s[pos[i]+1]);
}