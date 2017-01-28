#include <cstdio>
#include <vector>
#define foreach(v, c)               for( typeof( (c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define L(x) x<<1
#define R(x) (x<<1)+1
using namespace std;

const int maxn = 100005;

int cnum;
vector<int> chain[maxn];
int chainHead[maxn], chainPos[maxn], chainIndex[maxn];
int subtree[maxn];

vector<vector<int > > tree;
vector<int>color;
int parent[maxn];

inline void fastRead_int(int &x) {
    register int c = getchar();
    x = 0;
    int neg = 0;

    for(; ((c<48 || c>57) && c != '-'); c = getchar());

    if(c=='-') {
    	neg = 1;
    	c = getchar();
    }

    for(; c>47 && c<58 ; c = getchar()) {
    	x = (x<<1) + (x<<3) + c - 48;
    }

    if(neg)
    	x = -x;
}

struct node
{
	bool flag;
	int pos;
};

struct segTree
{
	int N,id;
	vector<node> tree;

	void createTree(vector<int> array,int chainId)
	{
		int log=0;
		N=array.size();
		if(N==0) return;

		node temp;
		temp.flag=false;
		temp.pos=-1;

		for(log=0;1<<log<N;++log);++log;
		tree=vector<node>((1<<log),temp);
		id=chainId;
	}

	void updateTree(int pos,int val)
	{
		update(1,0,N-1,pos,val);
	}

	void update(int index,int i,int j,int pos,int val)
	{
		if(i==j)
		{
			if(!val)
			{
				tree[index].pos=chain[id][i];
				tree[index].flag=true;
			}
			else
			{
				tree[index].flag=false;
				tree[index].pos=-1;
			}
			return;
		}

		int mid=(i+j)>>1;

		if(pos<=mid) update(L(index),i,mid,pos,val);
		else update(R(index),mid+1,j,pos,val);

		node left,right;

		left=tree[L(index)];
		right=tree[R(index)];

		if(right.flag)
		{
			tree[index].flag=true;
			tree[index].pos=right.pos;
		}
		else if(left.flag)
		{
			tree[index].flag=true;
			tree[index].pos=left.pos;
		}
		else
		{
			tree[index].flag=false;
			tree[index].pos=-1;
		}

	}

	int queryTree(int left,int right)
	{
		node x=query(1,0,N-1,left,right);
		return x.pos;
	}

	node query(int index,int i,int j,int left,int right)
	{
		if(left==i && right==j)
			return tree[index];

		int mid=(i+j)>>1;

		if(right<=mid)	return query(L(index),i,mid,left,right);
		else if(left >mid) return query(R(index),mid+1,j,left,right);
		else
		{
			node res1,res2,res;

			res1=query(L(index),i,mid,left,mid);
			res2=query(R(index),mid+1,j,mid+1,right);

			if(res2.flag)
			{
				res.flag=true;
				res.pos=res2.pos;
			}
			else if(res1.flag)
			{
				res.flag=true;
				res.pos=res1.pos;
			}
			else
			{
				res.flag=false;
				res.pos=-1;
			}


			return res;

		}

	}

};

int dfs(int u,int par)
{

	int its=0;

	for(int i=0;i<(int)tree[u].size();++i)
	{
		int v;

		v=tree[u][i];

		if(v!=par)
		{
			parent[v]=u;
			its+=dfs(v,u);
		}
	}
	return subtree[u]=its+1;
}



void HLD(int u)
{
  if(chain[cnum].size() == 0)
    chainHead[cnum] = u;

  chain[cnum].push_back(u);
  chainPos[u] = chain[cnum].size() - 1;
  chainIndex[u] = cnum;

  int most = 0, ind = -1;
  foreach(it, tree[u])
  {
    int v = *it;
    if(v == parent[u]) continue;
    if(subtree[v] > most)
      most = subtree[v], ind = v;
  }

  if(ind >=0) HLD(ind);

  foreach(it, tree[u])
  {
    int v = *it;
    if(v == parent[u] || v == ind) continue;
    ++cnum;
    HLD(v);
  }

}

vector<segTree> segments;

void build_segment()
{
	segTree t;
	segments=vector<segTree>(cnum+1,t);

	for(int i=0;i<=cnum;++i)
		segments[i].createTree(vector<int>(chain[i]),i);

}

int query(int u)
{
	if(u==-1) return -1;
	int res=segments[chainIndex[u]].queryTree(0,chainPos[u]);
	if(res!=-1) return res;
	return query(parent[chainHead[chainIndex[u]]]);
}

void change(int u)
{
	int chainId=chainIndex[u];
	int temp=color[chain[chainId][chainPos[u]]]=1-color[chain[chainId][chainPos[u]]];
	segments[chainId].updateTree(chainPos[u],temp);
}

int N,Q;

void read_input()
{
	fastRead_int(N);
	fastRead_int(Q);
	tree=vector<vector<int> >(N+1,vector<int>(0,0));
	for(int i=0;i<N-1;++i)
	{
		int u,v;
		fastRead_int(u);
		fastRead_int(v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	color=vector<int>(N+1,1);
	parent[1]=-1;
	cnum=0;
	dfs(1,-1);
	HLD(1);
	build_segment();

}

void solve()
{
	for(int i=0;i<Q;++i)
	{
		int u,v;
		fastRead_int(u);
		fastRead_int(v);
		if(u==0)
			change(v);
		else
			printf("%d\n",query(v));
	}
}


int main()
{
	read_input();
	solve();
	return 0;
}



olve();
	return 0;
}



