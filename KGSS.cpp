#include <cstdio>
#include <iostream>

#define L(x)	x<<1
#define R(x)	(x<<1) +1

const int TMAX=1<<18,IMAX=100000;

using namespace std;

struct node
{
	int best,secondBest;
}tree[TMAX];

int input[IMAX+2];

node merge(node &y,node &z)
{
	node x;
	int temp;

	x.best=max(y.best,z.best);
	temp=min(y.best,z.best);
	x.secondBest=max(max(y.secondBest,z.secondBest),temp);

	return x;
}

void init(int index,int i,int j)
{
	if(i==j)
	{
		tree[index].best=input[i];
		tree[index].secondBest=-1;
		return;
	}

	int mid=(i+j)>>1;

	init(L(index),i,mid);
	init(R(index),mid+1,j);

	node &x=tree[index];
	node &y=tree[L(index)];
	node &z=tree[R(index)];

	x=merge(y,z);

}

node query(int index,int i,int j,int left,int right)
{
	if(i==left && j==right)
		return tree[index];

	int mid=(i+j)>>1;

	if(right<=mid)	return query(L(index),i,mid,left,right);
	else if(left>mid)	return query(R(index),mid+1,j,left,right);
	else
	{
		node x,y;

		x=query(L(index),i,mid,left,mid);
		y=query(R(index),mid+1,j,mid+1,right);

		return merge(x,y);
	}
}

void update(int index,int i,int j,int pos,int val)
{
	if(i==j && i==pos)
	{
		tree[index].best=val;
		tree[index].secondBest=-1;
		return;
	}

	int mid=(i+j)>>1;

	if(pos<=mid)	update(L(index),i,mid,pos,val);
	else	update(R(index),mid+1,j,pos,val);

	tree[index]=merge(tree[L(index)],tree[R(index)]);

}

void printTree(int index,int i,int j)
{
	if(i==j)
	{
		printf("\n (%d,%d) %d %d ",i,j,tree[index].best,tree[index].secondBest);
		return;
	}

	int mid=(i+j)>>1;

	printTree(L(index),i,mid);
	printTree(R(index),mid+1,j);

	printf("\n (%d,%d) %d %d ",i,j,tree[index].best,tree[index].secondBest);
}

int main()
{
	int n,u,v,q;
	char str[2];

	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&input[i]);

	init(1,1,n);

	scanf("%d",&q);
	for(int i=0;i<q;++i)
	{
		scanf("%s %d %d",str,&u,&v);

		if(str[0]=='Q')
		{
			node res=query(1,1,n,u,v);
			printf("%d\n",res.best+res.secondBest);
		}
		else
			update(1,1,n,u,v);
	}


	return 0;
}
