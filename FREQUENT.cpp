#include <cstdio>
#include <iostream>

#define L(x)	x<<1
#define R(x)	(x<<1) +1

const int TMAX=1<<18,IMAX=100000;

using namespace std;

struct node
{
	int leftF,maxF,rightF;
}tree[TMAX];

int input[IMAX+2];

node merge(node &y,node &z,int l,int mid,int r)
{
	node x;


	if(input[mid]==input[mid+1])
	{
		x.leftF=y.leftF+(input[l]==input[mid]?(z.leftF):(0));

		x.rightF=z.rightF+(input[mid+1]==input[r]?y.rightF:0);
		x.maxF=max(y.maxF,z.maxF);
		int temp=(y.rightF+z.leftF);
		x.maxF=max(x.maxF,temp);

	}
	else
	{
		x.leftF=y.leftF;
		x.rightF=z.rightF;
		x.maxF=max(y.maxF,z.maxF);
	}

	return x;
}

void init(int index,int i,int j)
{
	if(i==j)
	{
		tree[index].leftF=tree[index].maxF=tree[index].rightF=1;

		return;
	}

	int mid=(i+j)>>1;

	init(L(index),i,mid);
	init(R(index),mid+1,j);

	node &x=tree[index];
	node &y=tree[L(index)];
	node &z=tree[R(index)];

	x=merge(y,z,i,mid,j);

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

		return merge(x,y,left,mid,right);
	}


}

void printTree(int index,int i,int j)
{
	if(i==j)
	{
		printf("\n (%d,%d) %d %d %d",i,j,tree[index].leftF,tree[index].maxF,tree[index].rightF);
		return;
	}

	int mid=(i+j)>>1;

	printTree(L(index),i,mid);
	printTree(R(index),mid+1,j);

	printf("\n (%d,%d) %d %d %d",i,j,tree[index].leftF,tree[index].maxF,tree[index].rightF);
}

int main()
{
	int n, q, i, u, v;
	while(scanf("%d", &n)==1 && n) {
		scanf("%d", &q);
		for(i = 1; i <= n; i++) scanf("%d", &input[i]);
		init(1, 1, n);
		for(i = 0; i < q; i++) {
			scanf("%d%d", &u, &v);
			if(u==v) printf("1\n");
			else
			{
				node x=query(1,1,n,u,v);
				printf("%d\n",x.maxF);
			}
		}
	}
	return 0;
}
