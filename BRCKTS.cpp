#include <stdio.h>
#include <iostream>
#define L(x)	x<<1
#define R(x)	(x<<1)+1
const int MAX=65536;

struct node
{
	int sum,minSum;
}T[MAX];

char input[32768];

using namespace std;

node combine(node left,node right)
{
	node temp;

	temp.sum=left.sum+right.sum;
	temp.minSum=min(left.minSum,left.sum+right.minSum);

	return temp;
}

void init(int index,int i,int j)
{
	if(i==j)
	{
		T[index].sum=T[index].minSum=(input[i-1]=='(')?1:-1;
		return;
	}

	int mid=(i+j)>>1;

	init(L(index),i,mid);
	init(R(index),mid+1,j);

	T[index]=combine(T[L(index)],T[R(index)]);
}

void update(int index,int i,int j,int pos)
{
	if(i==j && i==pos)
	{
		T[index].sum=T[index].minSum=-T[index].sum;
		return;
	}

	int mid=(i+j)>>1;

	if(pos<=mid)
		update(L(index),i,mid,pos);
	else
		update(R(index),mid+1,j,pos);

	T[index]=combine(T[L(index)],T[R(index)]);
}

int main()
 {
	int len, q, i, idx, test = 1;
	while(scanf("%d", &len)==1) {
		scanf("%s", input);
		init(1, 1, len);
		printf("Test %d:\n", test++);
		scanf("%d", &q);
		for(i=0; i<q; i++) {
			scanf("%d", &idx);
			if(!idx) {
				if(!T[1].sum && !T[1].minSum) printf("YES\n");
				else printf("NO\n");
			}
			else update(1, 1, len, idx);
		}
	}
	return 0;
}
