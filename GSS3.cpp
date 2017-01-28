#include <cstdio>
#include <iostream>
#include <math.h>
using namespace std;


struct Tree { int maxv, sum, lval, rval; };
const int MAX = 1 << 16;
int a[MAX+1];
Tree T[MAX << 1];

void init(int Node, int i, int j) {
	if(i==j) {
		T[Node].maxv = T[Node].sum = T[Node].rval = T[Node].lval = a[i];
		return;
	}
	int m = (i+j)/2;
	init(2*Node, i, m);
	init(2*Node+1, m+1, j);
	T[Node].sum = T[Node*2].sum + T[Node*2+1].sum;
	T[Node].maxv = max(max(T[2*Node].maxv, T[2*Node].rval + T[2*Node+1].lval), T[2*Node+1].maxv);
	T[Node].lval = max(T[2*Node].lval, T[2*Node].sum + T[2*Node+1].lval);
	T[Node].rval = max(T[2*Node].rval + T[2*Node+1].sum, T[2*Node+1].rval);
}

void update(int Node,int i,int j,int index,int val)
{

	if(i==j && i==index)
	{
		T[Node].lval=T[Node].rval=T[Node].maxv=T[Node].sum=val;
		return;
	}

	int mid=(i+j)>>1;

	if(index<=mid)
		update(2*Node,i,mid,index,val);
	else
		update(2*Node+1,mid+1,j,index,val);

	T[Node].sum = T[Node*2].sum + T[Node*2+1].sum;
	T[Node].maxv = max(max(T[2*Node].maxv, T[2*Node].rval + T[2*Node+1].lval), T[2*Node+1].maxv);
	T[Node].lval = max(T[2*Node].lval, T[2*Node].sum + T[2*Node+1].lval);
	T[Node].rval = max(T[2*Node].rval + T[2*Node+1].sum, T[2*Node+1].rval);
}

void find(Tree &res, int Node, int L, int R, int i, int j) {
	if(L==i && R==j) {
		res = T[Node];
		return;
	}
	int m = (L + R)/2;
	if(j<=m) find(res, 2*Node, L, m, i, j);
	else if(i>m) find(res, 2*Node+1, m+1, R, i, j);
	else {
		Tree Left, Right;
		find(Left, 2*Node, L, m, i, m);
		find(Right, 2*Node+1, m+1, R, m+1, j);

		res.sum = Left.sum + Right.sum;
		res.lval = max(Left.lval, Left.sum + Right.lval);
		res.rval = max(Left.rval + Right.sum, Right.rval);
		res.maxv = max(max(Left.maxv, Right.maxv), Left.rval + Right.lval);
	}
}

int main() {
	int n, i, j, m,q;
	Tree res;
	scanf("%d", &n);
	for(i=1; i<=n; i++) scanf("%d", &a[i]);
	init(1, 1, n);
	scanf("%d", &m);
	while(m--) {
		scanf("%d %d %d",&q, &i, &j);
		if(q==1)
		{
			find(res, 1, 1, n, i, j);
			printf("%d\n", res.maxv);
		}
		else
			update(1,1,n,i,j);
	}
	return 0;
}
