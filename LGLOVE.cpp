#include <bits/stdc++.h>
#define NMAX 333333
#define MOD 1000000007
#define L(x) (x<<1)
#define R(x) (L(x)|1)

using namespace std;
typedef long long int ll;
const ll inf=(1LL<<56);

int prime[NMAX],tot[NMAX],last[NMAX];
ll lcm[NMAX];
int N,Q;

void sieve(){
	for(int i=2;i<NMAX;++i){
		if(!prime[i]){
			for(int j=i;j<NMAX;j+=i){
				prime[j]=1;
				tot[j]++;
				last[j]=i;
			}
		}
	}
	lcm[1]=1;
	for(int i=2;i<NMAX;++i){
		if(tot[i]==1) lcm[i]=(lcm[i-1]*((ll)last[i]))%MOD;
		else lcm[i]=lcm[i-1];
	}
}

struct node{
	ll lazy;
	ll mn,mx;
	node(){
		mn=mx=lazy=0;
	}
	node(ll x){
		mn=mx=x;
		lazy=0;
	}
	node(ll x,ll y){
		mn=x;mx=y;
		lazy=0;
	}

};
node tree[NMAX<<2];
node null(inf,-inf);

ll input[NMAX];

inline node merge(node x,node y){
	return node(min(x.mn,y.mn),max(x.mx,y.mx));
}

inline void pushDown(int index,int i,int j){
	if(tree[index].lazy){
		tree[index].mn+=tree[index].lazy;
		tree[index].mx+=tree[index].lazy;
		if(i!=j){
			tree[L(index)].lazy+=tree[index].lazy;
			tree[R(index)].lazy+=tree[index].lazy;
		}
		tree[index].lazy=0;
	}
}

inline void setNode(int index,int i,int j,ll val){
	tree[index].mn+=val;
	tree[index].mx+=val;
	if(i!=j){
		tree[L(index)].lazy+=val;
		tree[R(index)].lazy+=val;
	}
}

void build(int index,int i,int j){
	if(i==j){
		tree[index]=node(input[i-1]);
		return;
	}
	int mid=(i+j)>>1;
	build(L(index),i,mid);
	build(R(index),mid+1,j);
	tree[index]=merge(tree[L(index)],tree[R(index)]);
}

void update(int index,int i,int j,int left,int right,ll val){
	pushDown(index,i,j);
	if(i>=left && j<=right){
		setNode(index,i,j,val);
		return;
	}
	if(i>right || j<left) return;

	int mid=(i+j)>>1;
	update(L(index),i,mid,left,right,val);
	update(R(index),mid+1,j,left,right,val);
	tree[index]=merge(tree[L(index)],tree[R(index)]);
}

node query(int index,int i,int j,int left,int right){
	pushDown(index,i,j);

	if(i>=left && j<=right) return tree[index];
	if(i>right || j<left) return null;

	int mid=(i+j)>>1;
	node x=query(L(index),i,mid,left,right);
	node y=query(R(index),mid+1,j,left,right);

	tree[index]=merge(tree[L(index)],tree[R(index)]);
	return merge(x,y);
}

void print(int index,int i,int j){
	if(i==j){
		cout<<i<<","<<j<<"---"<<tree[index].lazy<<" "<<tree[index].mx<<" "<<tree[index].mn<<endl;
		return;
	}
	int mid=(i+j)>>1;
	print(L(index),i,mid);
	print(R(index),mid+1,j);
	cout<<i<<","<<j<<"---"<<tree[index].lazy<<" "<<tree[index].mx<<" "<<tree[index].mn<<endl;
}

int main(){
	sieve();
	scanf("%d %d",&N,&Q);

	for(int i=0;i<N;++i) scanf("%lld",&input[i]);
	build(1,1,N);
	//print(1,1,N);

	for(int i=0;i<Q;++i){
		int u,v,w;
		ll x;

		scanf("%d %d %d",&u,&v,&w);
		++v,++w;
		switch(u){
		case 0:
				scanf("%lld",&x);
				update(1,1,N,v,w,x);
				break;
		case 1:
				printf("%lld\n",lcm[query(1,1,N,v,w).mx]);
				break;
		case 2:
				printf("%lld\n",lcm[query(1,1,N,v,w).mn]);
				break;
		}
	}

	return 0;
}
