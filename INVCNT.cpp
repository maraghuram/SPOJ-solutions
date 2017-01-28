#include <cstdio>
#include <iostream>

using namespace std;

const int MAX=200002;

int A[MAX],B[MAX];

long long int inv_count;

void merge(int l,int mid,int r)
{
	int i,j,k;

	j=i=l;
	k=mid+1;

	while(j<=mid && k<=r)
	{
		if(A[j]<A[k])
		{
			B[i]=A[j];
			++j;
		}
		else
		{
			B[i]=A[k];
			inv_count+=(mid-j)+1;
			++k;

		}
		++i;
	}

	while(j<=mid)
	{
		B[i]=A[j];
		++j;
		++i;
	}

	while(k<=r)
	{
		B[i]=A[k];
		++k;
		++i;
	}

	for(i=l;i<=r;++i)
	{
		A[i]=B[i];
	}
}

void partition(int l,int r)
{
	if(l<r)
	{
		int mid=(l+r)>>1;

		partition(l,mid);
		partition(mid+1,r);
		merge(l,mid,r);
	}
}


int main()
{
	int T;

	scanf("%d",&T);

	while(T>0)
	{

		int N;

		scanf("%d",&N);

		for(int i=0;i<N;++i)
			scanf("%d",&A[i]);

		inv_count=0;
		partition(0,N-1);

		printf("%lld\n",inv_count);

		--T;
	}

	return 0;
}
