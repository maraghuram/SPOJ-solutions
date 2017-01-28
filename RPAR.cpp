#include <cstdio>
#include <iostream>

using namespace std;
#define L(x) x<<1
#define R(x) (x<<1)+1
#define MOD 10007

const int MAX=1<<18;

struct node
{
	int sumSq,sum;
	int ft,st,tt;
}tree[MAX];

struct lazyNode
{
	int a,b,c;
}lazy[MAX];

bool notEmpty(lazyNode &x)
{
	return (x.a|x.b|x.c);
}

void merge(node &x,node &y,node &z)
{
	x.ft=(y.ft+z.ft)%MOD;
	x.st=(y.st+z.st)%MOD;
	x.tt=(y.tt+z.tt)%MOD;

	x.sumSq=(y.sumSq+z.sumSq)%MOD;
	x.sum=(y.sum+z.sum)%MOD;
}

void split(int index,int i,int j)
{
	node &x=tree[index];
	lazyNode &y=lazy[index];

	if(notEmpty(lazy[index]))
	{
		x.ft=(x.ft+(x.sumSq*y.a)%MOD)%MOD;
		x.st=(x.st+(x.sum*y.b)%MOD)%MOD;
		x.tt=(x.tt+(((y.c)%MOD*(j-i+1))%MOD)%MOD)%MOD;

		if(i!=j)
		{
			lazy[L(index)].a=(lazy[L(index)].a+y.a)%MOD;
			lazy[L(index)].b=(lazy[L(index)].b+y.b)%MOD;
			lazy[L(index)].c=(lazy[L(index)].c+y.c)%MOD;

			lazy[R(index)].a=(lazy[R(index)].a+y.a)%MOD;
			lazy[R(index)].b=(lazy[R(index)].b+y.b)%MOD;
			lazy[R(index)].c=(lazy[R(index)].c+y.c)%MOD;
		}
		y.a=y.b=y.c=0;
	}
}

void init(int index,int i,int j)
{
	if(i==j)
	{
		tree[index].sumSq=((i%MOD)*(i%MOD))%MOD;
		tree[index].sum=i%MOD;
		tree[index].ft=tree[index].st=tree[index].tt=0;
		lazy[index].a=lazy[index].b=lazy[index].c=0;
		return;
	}

	int mid=(i+j)>>1;

	init(L(index),i,mid);
	init(R(index),mid+1,j);

	merge(tree[index],tree[L(index)],tree[R(index)]);
}

void update(int index,int i,int j,int left,int right,int a,int b,int c)
{
	split(index,i,j);

	if(i>=left && j<=right)
	{
		node &x=tree[index];

		x.ft=(x.ft+(x.sumSq*a)%MOD)%MOD;
		x.st=(x.st+(x.sum*b)%MOD)%MOD;
		x.tt=(x.tt+((c%MOD)*(j-i+1))%MOD)%MOD;

		if(i!=j)
		{
			lazy[L(index)].a=(lazy[L(index)].a+a)%MOD;
			lazy[L(index)].b=(lazy[L(index)].b+b)%MOD;
			lazy[L(index)].c=(lazy[L(index)].c+c)%MOD;

			lazy[R(index)].a=(lazy[R(index)].a+a)%MOD;
			lazy[R(index)].b=(lazy[R(index)].b+b)%MOD;
			lazy[R(index)].c=(lazy[R(index)].c+c)%MOD;
		}

		return;
	}

	if(left>j || right<i)
		return;

	int mid=(i+j)>>1;

	update(L(index),i,mid,left,right,a,b,c);
	update(R(index),mid+1,j,left,right,a,b,c);


	merge(tree[index],tree[L(index)],tree[R(index)]);
}

void query(int index,int i,int j,int left,int right,int &result)
{
	split(index,i,j);

	node &x=tree[index];

	if(i>=left && j<=right)
	{
		result=(result+((x.ft+x.st)%MOD+x.tt)%MOD)%MOD;
		return;
	}

	if(left>j || right<i)
		return;

	int mid=(i+j)>>1;


	query(L(index),i,mid,left,right,result);
	query(R(index),mid+1,j,left,right,result);


	merge(tree[index],tree[L(index)],tree[R(index)]);
}

void printTree(int index,int i,int j)
{
	if(i==j)
	{
		printf("\n(%d,%d) %d %d %d %d %d  %d %d %d",i,j,tree[index].ft,tree[index].st,tree[index].tt,tree[index].sum,tree[index].sumSq,lazy[index].a,lazy[index].b,lazy[index].c);
		return;
	}

	int mid=(i+j)>>1;

	printTree(L(index),i,mid);
	printTree(R(index),mid+1,j);

	printf("\n(%d,%d) %d %d %d %d %d  %d %d %d",i,j,tree[index].ft,tree[index].st,tree[index].tt,tree[index].sum,tree[index].sumSq,lazy[index].a,lazy[index].b,lazy[index].c);
}


int main()
{
	int M,N;

	scanf("%d %d",&N,&M);

	init(1,0,N-1);

	for(int i=0;i<M;++i)
	{
		int q,x0,x1;

		scanf("%d %d %d",&q,&x0,&x1);

		if(q==0)
		{
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			update(1,0,N-1,x0,x1,a,b,c);
		}
		else
		{
			int res=0;
			query(1,0,N-1,x0,x1,res);
			printf("%d\n",res%MOD);
		}

	}




	return 0;
}
