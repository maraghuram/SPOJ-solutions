#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;


struct Tree { int lightsOn; };
const int MAX = 200064,BUFF = 128, PARAM = 4;;
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

void update(int Node,int i,int j,int updateLeft,int updateRight)
{
	if(lazy[Node])
	{
		if(lazy[Node]%2)
			T[Node].lightsOn=(j-i+1)-T[Node].lightsOn;

		if(i!=j)
		{
			lazy[2*Node]+=lazy[Node];
			lazy[2*Node+1]+=lazy[Node];
		}

		lazy[Node]=0;
	}


	if(updateLeft<=i && j<=updateRight)
	{
		T[Node].lightsOn=(j-i+1)-T[Node].lightsOn;

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


	T[Node].lightsOn=T[2*Node].lightsOn+T[2*Node+1].lightsOn;
}

void find(int Node, int i,int j,int queryLeft,int queryRight,int &ans)
{
	if(lazy[Node])
	{
		if(lazy[Node]%2)
					T[Node].lightsOn=(j-i+1)-T[Node].lightsOn;

		if(i!=j)
		{
			lazy[2*Node]+=lazy[Node];
			lazy[2*Node+1]+=lazy[Node];
		}

		lazy[Node]=0;
	}

	if(queryLeft<=i && j<=queryRight)
	{
		ans+=T[Node].lightsOn;
		return;
	}
	if(queryLeft>j || queryRight<i)
		return;

	int m = (i + j)/2;

	if(i==j)
		return;

	find(2*Node, i, m, queryLeft, queryRight,ans);
	find(2*Node+1, m+1, j,queryLeft, queryRight,ans);

	T[Node].lightsOn=T[2*Node].lightsOn+T[2*Node+1].lightsOn;

}

void printTree(int node,int i,int j)
{
	if(i==j)
	{
		printf("\n (%d,%d)- %d %d",i,j,T[node].lightsOn,lazy[node]);
		return;
	}

	int mid=(i+j)>>1;

	printTree(2*node,i,mid);
	printTree(2*node+1,mid+1,j);

	printf("\n (%d,%d)- %d %d",i,j,T[node].lightsOn,lazy[node]);
}

int main() {
	int n, i, j, m,q,*param;
	int res;

	param = readln(), n = param[0], m = param[1];

	while(m--) {
		res=0;
		param = readln(), q = param[0], i = param[1], j = param[2];
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
