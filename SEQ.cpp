#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long int x64;
typedef vector<vector<x64> > vvl;
typedef vector<x64> vl;

const x64 MOD=1000000000;

vvl Identity;

vvl matrix_multiply(vvl A,vvl B)
{
	vvl C=vvl(A.size(),vl(B[0].size()));

	for(int i=0;i<A.size();++i)
		for(int j=0;j<B[0].size();++j)
		{
			C[i][j]=0;
			for(int k=0;k<A[0].size();++k)
				C[i][j]=(C[i][j]+(A[i][k]*B[k][j])%MOD)%MOD;
		}

	return C;
}

vvl matrix_power(vvl A,int power)
{
	if(power==0) return Identity;
	if(power==1) return A;
	if(power%2) return matrix_multiply(matrix_power(A,power-1),A);

	vvl temp=vvl(matrix_power(A,power/2));

	return (matrix_multiply(temp,temp));
}


int main()
{
	int T;
	scanf("%d",&T);

	while(T>0)
	{
		int K,N;
		scanf("%d",&K);

		vvl base=vvl(K);
		vvl coff=vvl(K);
		Identity=vvl(K,vl(K));
		for(int i=0;i<K;++i)
			for(int j=0;j<K;++j)
			{
				if(i==j) Identity[i][i]=1;
				else Identity[i][j]=0;
			}

		for(int i=0;i<K;++i)
		{
			base[K-i-1]=vl(1);
			scanf("%lld",&base[K-i-1][0]);
		}

		for(int i=0;i<K;++i)
		{
			coff[i]=vl(K,0);
			scanf("%lld",&coff[0][i]);
		}

		for(int i=1;i<K;++i)
			coff[i][i-1]=1;

		scanf("%d",&N);
		if(N<=K) printf("%lld\n",base[N-1][0]);
		else
		{
			x64 result=0;
			vvl temp=matrix_power(coff,N-K);

	/*		for(int i=0;i<K;++i)
			{
				printf("\n");
				for(int j=0;j<K;++j)
					printf("%lld ",temp[i][j]);
			}
*/
			for(int i=0;i<K;++i) result=(result+temp[0][i]*base[i][0])%MOD;
			printf("%lld\n",result);
		}

		--T;
	}
	return 0;
}
