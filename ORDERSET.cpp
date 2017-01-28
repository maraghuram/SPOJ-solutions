#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct query
{
	char op;
	int x;
}dummy;

vector<int>	tree,B;
set<int> input;
vector<query> queries;
int maxVal=1;

void update(int idx,int val)
{
	while(idx<tree.size())
	{
		tree[idx]+=val;
		idx+=( idx & -idx);
	}
}

int query(int idx)
{
	int res=0;

	while(idx>0)
	{
		res+=tree[idx];
		idx-=( idx & -idx);
	}

	return res;
}

int search(int cumfreq)
{
	int low,mid,high;

	low=1;
	high=maxVal;


	while(low<=high)
	{
		mid=(low+high)>>1;
		if(query(mid)>=cumfreq)	high=mid-1;
		else	low=mid+1;
	}

	if(low>maxVal)
		return -1;
	else
		return low;
}

int main()
{
	dummy.op=' ';
	dummy.x=0;

	int N;

	scanf("%d",&N);

	queries.resize(N,dummy);
	B.resize(N,0);

	for(int i=0;i<N;++i)
	{
		char str[3];
		int val;

		scanf("%s %d",str,&val);
		queries[i].op=str[0];
		queries[i].x=val;
		B[i]=val;
	}

	sort(B.begin(),B.end());

	while(maxVal<=N)
		maxVal=maxVal<<1;
	tree.resize(maxVal+1,0);
	input=set<int>();

	for(int i=0;i<N;++i)
	{
		int rank=lower_bound(B.begin(),B.end(),queries[i].x)-B.begin()+1;
		int find;
		pair<set<int>::iterator,bool > ret;

		switch(queries[i].op)
		{
		case 'I':	ret=input.insert(queries[i].x);
					if(ret.second)	update(rank,1);
					break;

		case 'D':	if(input.erase(queries[i].x))	update(rank,-1);
					break;

		case 'C':	printf("%d\n",query(rank-1));
					break;

		case 'K':	find=search(queries[i].x);
					if(find==-1)
						printf("invalid\n");
					else
						printf("%d\n",B[find-1]);
					break;
		}
	}

	return 0;
}
