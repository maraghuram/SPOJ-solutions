#include <cstdio>
#include <vector>

typedef long long int ll;

const ll MOD = 1000000007;

using namespace std;

vector<vector<ll> > identity;

vector<vector<ll> > matrix_multiply(vector<vector<ll> > A,vector<vector<ll> > B)
{
	vector<vector<ll> > product=vector<vector<ll> >(2,vector<ll>(2,0));

	for(ll i=0;i<2;++i)
		for(ll j=0;j<2;++j)
		{
			product[i][j]=0;
			for(ll k=0;k<2;++k)
				product[i][j]=(product[i][j]+A[i][k]*B[k][j])%MOD;
		}


	return product;

}

vector<vector<ll> > matrix_power(vector<vector<ll> > M,ll N)
{
	vector<vector<ll> > result=vector<vector<ll> >(2,vector<ll>(2,0));
	if(N==0) return identity;
	if(N==1) return M;
	if(N%2)	return matrix_multiply(M,matrix_power(M,N-1));
	result=matrix_power(M,N/2);
	return matrix_multiply(result,result);
}

ll find_nth(ll N)
{
	if(N==1) return 0;
	if(N==2) return 1;

	N=N-1;

	vector<vector<ll> > T=vector<vector<ll> >(2,vector<ll>(2,0));
	T[0][0]=0;
	T[0][1]=T[1][0]=T[1][1]=1;

	T=matrix_power(T,N-1);

	return (T[0][0]+T[0][1])%MOD;
}


 int main()
{
	int T;

	identity=vector<vector<ll> >(2,vector<ll>(2,0));
	identity[0][0]=identity[1][1]=1;

	scanf("%d",&T);
	while(T>0)
	{
		ll res,i,j;

		scanf("%lld %lld",&i,&j);
		++i,++j;
		res=(find_nth(j+2)-find_nth(i+1))%MOD;

		if(res<0) res+=MOD;

		printf("%lld\n",res);
		--T;
	}

	return 0;
}
