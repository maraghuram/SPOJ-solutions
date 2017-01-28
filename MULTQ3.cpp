#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;


struct Tree { int div0,div1,div2; };
const int MAX = 1 << 18,BUFF = 128, PARAM = 4;;
int lazy[MAX];
Tree T[MAX];

static int *readln() {
	static char buff[BUFF], *p;
	static int param[PARAM];
	int idx = 0;
	fgets(buff, 128, stdin);
	p = strtok(buff, " ");
	while(p) {
		param[idx++] = atoi(p);
		p = strtok(0, " ");
	}
	return param;
}

void cyclicSwap(int &x,int &y,int &z)
{
	int temp=z;
	z=y;
	y=x;
	x=temp;
}

void init(int Node,int i,int j)
{
	if(i==j)
	{
		T[Node].div0=1;
		lazy[Node]=T[Node].div1=T[Node].div2=0;
		return;
	}

	int mid=(i+j)>>1;

	init(2*Node,i,mid);
	init(2*Node+1,mid+1,j);


	T[Node].div0=T[2*Node].div0+T[2*Node+1].div0;
	T[Node].div1=T[2*Node].div1+T[2*Node+1].div1;
	T[Node].div2=T[2*Node].div2+T[2*Node+1].div2;

}

void update(int Node,int i,int j,int updateLeft,int updateRight)
{
	if(lazy[Node])
	{
		int temp=lazy[Node];

		if(temp%3==1)
			cyclicSwap(T[Node].div0,T[Node].div1,T[Node].div2);
		else if(temp%3==2)
			cyclicSwap(T[Node].div0,T[Node].div2,T[Node].div1);

		if(i!=j)
		{
			lazy[2*Node]+=temp;
			lazy[2*Node+1]+=temp;
		}

		lazy[Node]=0;
	}


	if(updateLeft<=i && j<=updateRight)
	{
		cyclicSwap(T[Node].div0,T[Node].div1,T[Node].div2);

		if(i!=j)
		{
			lazy[2*Node]+=1;
			lazy[2*Node+1]+=1;
		}
		return;
	}


	if(updateLeft >j || updateRight< i )
		return;

	int mid=(i+j)>>1;

	if(i==j)
		return;

	update(2*Node,i,mid,updateLeft,updateRight);
	update(2*Node+1,mid+1,j,updateLeft,updateRight);


	T[Node].div0=T[2*Node].div0+T[2*Node+1].div0;
	T[Node].div1=T[2*Node].div1+T[2*Node+1].div1;
	T[Node].div2=T[2*Node].div2+T[2*Node+1].div2;
}

void find(int Node, int i,int j,int queryLeft,int queryRight,int &ans)
{
	if(lazy[Node])
	{
		int temp=lazy[Node];

		if(temp%3==1)
			cyclicSwap(T[Node].div0,T[Node].div1,T[Node].div2);
		else if(temp%3==2)
			cyclicSwap(T[Node].div0,T[Node].div2,T[Node].div1);

		if(i!=j)
		{
			lazy[2*Node]+=temp;
			lazy[2*Node+1]+=temp;
		}

		lazy[Node]=0;
	}

	if(queryLeft<=i && j<=queryRight)
	{
		ans+=T[Node].div0;
		return;
	}
	if(queryLeft>j || queryRight<i)
		return;

	int m = (i + j)/2;

	if(i==j)
		return;

	find(2*Node, i, m, queryLeft, queryRight,ans);
	find(2*Node+1, m+1, j,queryLeft, queryRight,ans);


	T[Node].div0=T[2*Node].div0+T[2*Node+1].div0;
	T[Node].div1=T[2*Node].div1+T[2*Node+1].div1;
	T[Node].div2=T[2*Node].div2+T[2*Node+1].div2;

}

void printTree(int node,int i,int j)
{
	if(i==j)
	{
		printf("\n (%d,%d)-%d %d %d %d",i,j,T[node].div0,T[node].div1,T[node].div2,lazy[node]);
		return;
	}

	int mid=(i+j)>>1;

	printTree(2*node,i,mid);
	printTree(2*node+1,mid+1,j);

	printf("\n (%d,%d)-%d %d %d %d",i,j,T[node].div0,T[node].div1,T[node].div2,lazy[node]);
}

int main() {
	int n, i, j, m,q,*param;
	int res;

	param = readln(), n = param[0], m = param[1];
	init(1,1,n);
	while(m--) {
		res=0;
		param = readln(), q = param[0], i = param[1], j = param[2];
		++i,++j;
		if(q==1)
		{
			find( 1, 1, n, i, j,res);
			printf("%d\n", res);
		}
		else
			update(1,1,n,i,j);

	}
	return 0;
}
