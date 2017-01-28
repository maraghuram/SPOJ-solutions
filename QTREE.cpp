#include <vector>
#include <iostream>
#include <cstdio>
#define NMAX 11111
#define sz size()
#define pb push_back
#define x first
#define y second
#define L(n) (n<<1)
#define R(n) ((n<<1)+1)
using namespace std;

typedef pair<int,int> pii;

vector< pii > adj[NMAX];
int subtree[NMAX],parent[NMAX],cost[NMAX],level[NMAX];

int dfs(int u,int p,int e,int d){
	int its=1;
	parent[u]=p;
	cost[u]=e;
	level[u]=d;

	for(int i=0;i<adj[u].sz;++i){
		int v=adj[u][i].x;
		int c=adj[u][i].y;
		if(v!=p){
			its+=dfs(v,u,c,d+1);
		}
	}
	subtree[u]=its;
	return its;
}

vector<int> chainVal[NMAX];
int chainHead[NMAX],chainId[NMAX],chainPos[NMAX];
int cnum;

void hld(int u){
	if(chainVal[cnum].sz==0) chainHead[cnum]=u;
	chainVal[cnum].pb(cost[u]);
	chainPos[u]=chainVal[cnum].sz-1;
	chainId[u]=cnum;

	int ind=-1,val=0;

	for(int i=0;i<adj[u].sz;++i){
		int v=adj[u][i].x;
		if(v!=parent[u]){
			if(subtree[v]>val) val=subtree[v],ind=v;
		}
	}

	if(ind!=-1) hld(ind);

	for(int i=0;i<adj[u].sz;++i){
		int v=adj[u][i].x;
		if(v!=parent[u] && v!=ind){
			++cnum;
			hld(v);
		}
	}
}

struct node{
	int best;
	node(){
		best=0;
	}
	node(int x){
		best=x;
	}
};

void merge(node &x,node &y,node &z){
	x.best=max(y.best,z.best);
}

struct chain{
	vector<int> base;
	vector<node> tree;
	int N;
	chain(vector<int> input){
		base=vector<int>(input);
		N=base.size();
		tree=vector<node>((N<<3)+2);
		init(1,0,N-1);
	}

	void init(int index,int i,int j){
		if(i==j){
			tree[index]=node(base[i]);
			return;
		}
		int mid=(i+j)>>1;
		init(L(index),i,mid);
		init(R(index),mid+1,j);

		merge(tree[index],tree[L(index)],tree[R(index)]);
	}

	node query(int index,int i,int j,int left,int right){
		if(i==left && j==right) return tree[index];

		int mid=(i+j)>>1;

		if(right<=mid) return query(L(index),i,mid,left,right);
		else if(left>mid) return query(R(index),mid+1,j,left,right);
		else{
			node result,l,r;
			l=query(L(index),i,mid,left,mid);
			r=query(R(index),mid+1,j,mid+1,right);
			merge(result,l,r);
			return result;
		}
	}

	void update(int index,int i,int j,int pos,int val){
		if(i==j && pos==i){
			tree[index]=node(val);
			return;
		}

		int mid=(i+j)>>1;
		if(pos<=mid) update(L(index),i,mid,pos,val);
		else update(R(index),mid+1,j,pos,val);

		merge(tree[index],tree[L(index)],tree[R(index)]);
	}

	node ask(int left,int right){
		if(left<=right && left<N) return query(1,0,N-1,left,right);
		else return node(0);

	}

	void upd(int pos,int val){
		update(1,0,N-1,pos,val);
	}
};

vector< chain* > chains;

int lca(int u,int v){

	while(chainId[u]!=chainId[v]){
		if(level[chainHead[chainId[u]]]<level[chainHead[chainId[v]]]) v=parent[chainHead[chainId[v]]];
		else u=parent[chainHead[chainId[u]]];
	}

	return (level[u]>level[v]?v:u);
}

node Query(int u,int lc){
	//printf("node %d %d %d %d %d\n",u,level[u],level[lc],chainId[u],chainId[lc]);
	node res,ans,temp;
	while(level[u]>level[lc]){
		if(chainId[u]==chainId[lc]) res=chains[chainId[u]]->ask(chainPos[lc]+1,chainPos[u]);
		else res=chains[chainId[u]]->ask(0,chainPos[u]);
		u=parent[chainHead[chainId[u]]];
		//printf("\t %d \n",u);
		merge(temp,ans,res);
		ans=temp;
	}
	return ans;
}

void Change(int u,int v,int val){
	int node=(level[u]>level[v]?u:v);
	chains[chainId[node]]->upd(chainPos[node],val);
}

vector< pii > edges;

int main(){
//	freopen("1.in","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--){
		int N;
		edges.clear();
		scanf("%d",&N);
		for(int i=0;i<=N;++i) adj[i].clear(),chainVal[i].clear();

		for(int i=0;i<N-1;++i){
			int u,v,c;
			scanf("%d %d %d",&u,&v,&c);
			adj[v].pb(pii(u,c));
			adj[u].pb(pii(v,c));
			edges.pb(pii(u,v));
		}

		dfs(1,0,0,1);
		cnum=0;
		hld(1);
		chains.clear();
		for(int i=0;i<=cnum;++i){
			chains.pb((chain*)new chain(chainVal[i]));
		}

		char type[10];
		while(1){
			int u,v;
			scanf("%s",type);
			if(type[0]=='C'){
				scanf("%d %d",&u,&v);
				Change(edges[u-1].x,edges[u-1].y,v);
			}
			else if(type[0]=='Q'){
				scanf("%d %d",&u,&v);
				node l,r,temp;
				int lc=lca(u,v);
				//printf("%d\n",lc);
				l=Query(u,lc);
				r=Query(v,lc);
				merge(temp,l,r);
				printf("%d\n",temp.best);
			}
			else break;
		}


	}

}
