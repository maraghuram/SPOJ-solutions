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

using namespace std;

struct minmax{
	int min,max,secondmax,secondmin;
	minmax(){
		min=max=secondmax=secondmin=0;
	}
	minmax(int x)
	{
		min=max=x;
		secondmax=INT_MIN;
		secondmin=INT_MAX;
	}
	minmax(int a,int b,int c,int d)
	{
		min=a;
		max=b;
		secondmax=c;
		secondmin=d;
	}
};

minmax operator+(const minmax &x,const minmax &y)
{
	int newmin=min(x.min,y.min);
	int newmax=max(x.max,y.max);
	int newsecondmax;
	int newsecondmin;

	if(newmax==x.max)	newsecondmax=max(x.secondmax,y.max);
	else newsecondmax=max(x.max,y.secondmax);

	if(newmin==x.min)	newsecondmin=min(x.secondmin,y.min);
	else newsecondmin=min(x.min,y.secondmin);

	return minmax(newmin,newmax,newsecondmax,newsecondmin);
}

struct node{
	int key,priority,size;
	minmax val;

	node *left,*right;
	node(int a,int b,int c,node *l,node *r){
		key=a;priority=b;size=c;left=l;right=r;
		val=minmax(a);
	}

};


node *nill = new node(0,-1,0,NULL,NULL);
node *root=nill;


void update(node *&root){
	if(root!=nill){
		root->size=root->left->size+root->right->size+1;
		root->val=minmax(root->key);
		if(root->left!=nill) root->val=root->left->val+root->val;
		if(root->right!=nill) root->val=root->val+root->right->val;
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

	if(root->left->priority>root->priority)	rotateRight(root);
	if(root->right->priority>root->priority) rotateLeft(root);
}

void insert(node *&root,int key){
	if(root==nill){
		root=new node(key,rand(),1,nill,nill);
		return;
	}

	if(key<root->key)	insert(root->left,key);
	else if(key>root->key)	insert(root->right,key);

	update(root);
	balance(root);
}

void remove(node *&root,int key){
	if(root==nill) return;

	if(root->key>key){
		remove(root->left,key);
		update(root);
		return;
	}
	else if(root->key<key){
		remove(root->right,key);
		update(root);
		return;
	}

	if(root->left==nill && root->right==nill){
		delete root;
		root=nill;
	}
	else{
		root->left->priority>root->right->priority?rotateRight(root):rotateLeft(root);
		remove(root,key);
	}
	update(root);
}

minmax query(node *&root,int i,int j,int left,int right){
	if(i==left && j==right){
		return root->val;
	}

	int mid=i+root->left->size;

	if(right<mid) return query(root->left,i,mid-1,left,right);
	if(left>mid) return query(root->right,mid+1,j,left,right);

	minmax res=minmax(root->key);
	if(left<mid) res=query(root->left,i,mid-1,left,mid-1)+res;
	if(right>mid) res=res+query(root->right,mid+1,j,mid+1,right);

	return res;

}

void printTree(node *root)
{
	if(root==nill) return;
	printf("%d %d %d %d\n",root->left->size,root->right->size,root->val.max,root->key);

	printTree(root->left);
	printTree(root->right);
}


int main(){
	minmax res;
	int Q;
	scanf("%d",&Q);
	srand((unsigned int)time(0));
	for(int i=0;i<Q;++i)
	{
		char type[5];
		int u,v;
		scanf("%s",type);
		switch(type[0]){

		case 'I' :  scanf("%d",&u);
					insert(root,u);
					break;
		case 'D' : 	scanf("%d",&u);
					remove(root,u);
					break;
		case 'N' :
		case 'X' :	scanf("%d %d",&u,&v);
					if(u==v) printf("%d\n",-1);
					else{
						res=query(root,0,root->size-1,u,v);
						if(type[0]=='N') printf("%d\n",min(res.max-res.secondmax,res.secondmin-res.min));
						else printf("%d\n",res.max-res.min);
					}
					break;
		}
		//printTree(root);
	}



	return 0;
}
