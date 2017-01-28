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

struct best_sum{
	int sum,max,pre,suf;
	best_sum(){
		sum=0;
		sum=max=pre=suf=000000;
	}
	best_sum(int x)
	{
		sum=max=pre=suf=x;
	}
	best_sum(int a,int b,int c,int d)
	{
		sum=a;
		max=b;
		pre=c;
		suf=d;
	}
};

best_sum operator+(const best_sum &x,const best_sum &y)
{
	return best_sum(x.sum+y.sum,max(x.suf+y.pre,max(x.max,y.max)),max(x.pre,x.sum+y.pre),max(y.suf,y.sum+x.suf));
}

struct node{
	int key,priority,size;
	best_sum val;

	node *left,*right;
	node(int a,int b,int c,node *l,node *r){
		key=a;priority=b;size=c;left=l;right=r;
		val=best_sum(a);
	}

};

node *nill = new node(0,-1,0,NULL,NULL);
node *root=nill;

void printTree(node *root)
{
	if(root==nill) return;
	printf("%d %d %d %d\n",root->left->size,root->right->size,root->val.max,root->key);

	printTree(root->left);
	printTree(root->right);
}

void update(node *&root){
	if(root!=nill){
		root->size=root->left->size+root->right->size+1;
		root->val=best_sum(root->key);
		if(root->left!=nill)
			root->val=root->left->val+root->val;
		if(root->right!=nill)
			root->val=root->val+root->right->val;
	}
}

void rotateLeft(node *&root){
	node *T=root->right;
	root->right=T->left;
	T->left=root;
	root=T;
	update(root->left);
	update(root);
}

void rotateRight(node *&root){
	node *T=root->left;
	root->left=T->right;
	T->right=root;
	root=T;
	update(root->right);
	update(root);
}

void balance(node *&root){
	if(root->left->priority>root->priority){
		rotateRight(root);
	}
	if(root->right->priority>root->priority){
		rotateLeft(root);
	}

}

void insert(node *&root,int index,int key){

	if(root==nill){
		root = new node(key,rand(),1,nill,nill);
		return;
	}

	if(index<=root->left->size){
		insert(root->left,index,key);
	}
	else{
		insert(root->right,index-root->left->size-1,key);
	}
	update(root);
	balance(root);
}

void erase(node *&root,int index)
{
	if(root==nill)
		return;

	if(index<root->left->size)
	{
		erase(root->left,index);
		update(root);
		return;
	}
	if(index>root->left->size)
	{
		erase(root->
				right,index-root->left->size-1);
		update(root);
		return;
	}

	if(root->left==nill && root->right==nill){
		delete root;
		root=nill;
	}
	else
	{
		root->left->priority>root->right->priority?rotateRight(root):rotateLeft(root);
		erase(root,index);
	}
	update(root);

}

void replace(node *&root,int index,int val)
{
	if(root==nill)
		return;

	if(index<root->left->size)
	{
		replace(root->left,index,val);
		update(root);
		return;
	}

	if(index>root->left->size)
	{
		replace(root->right,index-root->left->size-1,val);
		update(root);
		return;
	}

	root->key=val;
	update(root);

}

best_sum max(node *&root,int i,int j,int left,int right)
{
	//printf("\n%d %d- %d %d %d %d\n",i,j,root->val.sum,root->val.max,root->val.pre,root->val.suf);
	if(i==left && j==right){

		return root->val;
	}

	int mid=root->left->size+i;
	//printf("\t%d %d %d %d %d\n",i,j,left,right,mid);
	if(right<mid){
		return max(root->left,i,mid-1,left,right);
	}

	if(left>mid){
		return max(root->right,mid+1,j,left,right);
	}

	best_sum ans(root->key);
	if(left<mid)
	{
		ans=max(root->left,i,mid-1,left,mid-1)+ans;
		//printf("LEFT %d %d ",i,j);
		//printf("\t %d %d %d %d \t",ans.max,ans.sum,ans.suf,ans.pre);
	}
	if(right>mid)
	{
		ans=ans+max(root->right,mid+1,j,mid+1,right);
		//printf("RIGHT %d %d",i,j);
	}
	return ans;
}



int main()
{
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;++i)
	{
		int u;
		scanf("%d",&u);
		insert(root,i,u);
	}
	int Q;
	scanf("%d",&Q);
	srand((unsigned int)time(0));
	for(int i=0;i<Q;++i)
	{
		char type[5];
		int u,v;
		scanf("%s",type);
		switch(type[0]){

		case 'I' :  scanf("%d %d",&u,&v);
					insert(root,u-1,v);
					break;
		case 'D' : 	scanf("%d",&u);
					erase(root,u-1);
					break;
		case 'R' :	scanf("%d %d",&u,&v);
					replace(root,u-1,v);
					break;
		case 'Q' :	scanf("%d %d",&u,&v);
					printf("%d\n",max(root,0,root->size-1,u-1,v-1).max);
					break;
		}
	}

	return 0;
}
