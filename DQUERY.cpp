#include <cstdio>
#include <vector>
#include <algorithm>
#define L(x)  x<<1
#define R(x)  (x<<1)+1
using namespace std;

struct query
{
	int start,end,rank;
};


struct query_less {
    bool operator ()(query const& a, query const& b) const {
        if (a.end < b.end) return true;
        if (a.end > b.end) return false;

        if (a.rank < b.rank) return true;
        if (a.rank > b.rank) return false;

        return false;
    }
};

vector<query> q;
vector<int> input,tree,ans;
int position[1111111];

void count(int index,int i,int j,int left,int right,int &res)
{
	if(i==left && j==right)
	{
		res+=tree[index];
		return;
	}

	int mid=(i+j)>>1;

	if(right<=mid)
		count(L(index),i,mid,left,right,res);
	else if(left>mid)
		count(R(index),mid+1,j,left,right,res);
	else
	{
		count(L(index),i,mid,left,mid,res);
		count(R(index),mid+1,j,mid+1,right,res);
	}
}

void update(int index,int i,int j,int pos,int val)
{
	if(i==j && i==pos)
	{
		tree[index]+=val;
		return;
	}

	int mid=(i+j)>>1;

	if(pos<=mid) update(L(index),i,mid,pos,val);
	else update(R(index),mid+1,j,pos,val);

	tree[index]=tree[L(index)]+tree[R(index)];
}

void printTree(int index,int i,int j)
{
	if(i==j)
	{
		printf("\n %d %d %d",i,j,tree[index]);
		return;
	}

	int mid=(i+j)>>1;

	printTree(L(index),i,mid);
	printTree(L(index),mid+1,j);
	printf("\n %d %d %d",i,j,tree[index]);


}

int main()
{
	int N,Q,log;
	query dummy;

	scanf("%d",&N);

	input=vector<int>(N,0);

	for(log=0;1<<log<=N;++log);
	tree=vector<int>(1<<(log+1),0);

	for(int i=0;i<N;++i)
		scanf("%d",&input[i]);

	scanf("%d",&Q);

	dummy.end=dummy.rank=dummy.start=0;
	q=vector<query>(Q,dummy);
	ans=vector<int>(Q,0);

	for(int i=0;i<Q;++i)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		q[i].rank=i;
		q[i].start=u;
		q[i].end=v;

	}

	sort(q.begin(),q.end(),query_less());

	for(int i=0,k=0;i<N && k<Q;++i)
	{
		if(position[input[i]])		update(1,1,N,position[input[i]],-1);
		position[input[i]]=i+1;
		update(1,1,N,i+1,1);
		while(q[k].end==i+1 && k<Q)
		{
			int res=0;
			count(1,1,N,q[k].start,i+1,res);
			ans[q[k].rank]=res;
			++k;
		}
	}

	for(int i=0;i<Q;++i)
		printf("%d\n",ans[i]);

	return 0;
}
