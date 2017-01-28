// By noob.

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <complex>
#pragma comment(linker, "/STACK:266777216")

using namespace std;

#define assert(f) { if(!(f)) { fprintf(stderr,"Assertion failed: "); fprintf(stderr,#f); fprintf(stderr,"\n"); exit(1); } }

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<double> VD;
typedef pair<double,double> PDD;

const int inf=1000000000;
const LL INF=LL(inf)*inf;
const double eps=1e-9;
const double PI=2*acos(0.0);
#define bit(n) (1<<(n))
#define bit64(n) ((LL(1))<<(n))
#define pb push_back
#define sz size()
#define mp make_pair
#define cl clear()
#define all(a) (a).begin(),(a).end()
#define fill(ar,val) memset((ar),(val),sizeof (ar))
#define MIN(a,b) {if((a)>(b)) (a)=(b);}
#define MAX(a,b) {if((a)<(b)) (a)=(b);}
#define sqr(x) ((x)*(x))
#define X first
#define Y second

clock_t start=clock();

#define NMAX 111111

struct node{
	int key,priority,max,size;
	node *left,*right;
	node(int a,int b,int c,int d,node *l,node *r){
		key=a;
		priority=b;
		size=c;
		max=d;
		left=l;
		right=r;
	}
};

node *nill = new node(0,-1,0,-inf,NULL,NULL);
node *root=nill;

void update(node *root){
	if(root!=nill){
		root->size=root->left->size+root->right->size+1;
		root->max=max(root->key,max(root->left->max,root->right->max));
	}
}

node *rotateLeft(node *root){
	node *T=root->right;
	root->right=T->left;
	T->left=root;

	update(T->left);
	update(T);
	return T;
}

node *rotateRight(node *root){
	node *T=root->left;
	root->left=T->right;
	T->right=root;

	update(T->right);
	update(T);
	return T;
}

node *balance(node *root){
	if(root->left->priority>root->priority){
		return rotateRight(root);
	}
	if(root->right->priority>root->priority){
		return rotateLeft(root);
	}
	return root;
}

node *insert(node *root,int index,int key){

	if(root==nill){
		return new node(key,rand(),1,key,nill,nill);
	}

	if(index<=root->left->size){
		root->left=insert(root->left,index,key);
	}
	else{
		root->right=insert(root->right,index-root->left->size-1,key);
	}
	update(root);
	return balance(root);
}

int rmq(node *root,int i,int j,int left,int right)
{
	if(i==left && j==right){
		return root->max;
	}

	int mid=i+root->left->size;

	if(right< mid){
		return rmq(root->left,i,mid-1,left,right);
	}
	else if(left > mid ){
		return rmq(root->right,mid+1,j,left,right);
	}
	int ans=root->key;
	if(left<mid){
		ans=max(ans,rmq(root->left,i,mid-1,left,mid-1));
	}
	if(right>mid){
		ans=max(ans,rmq(root->right,mid+1,j,mid+1,right));
	}
	return ans;
}

int main()
{
	int Q;
	scanf("%d",&Q);
	srand((unsigned int)time(0));
	for(int i=0;i<Q;++i)
	{
		char type[5];
		int u,v;
		scanf("%s %d %d",type,&u,&v);
		if(type[0]=='A')
			root=insert(root,v-1,u);
		else
			printf("%d\n",rmq(root,0,root->size-1,u-1,v-1));
	}

	return 0;
}

