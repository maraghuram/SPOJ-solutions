#include <bits/stdc++.h>
#define NMAX 111111
using namespace std;

struct node{
  node *l,*r;
  int cnt;
  node(){
    l=r=NULL;
    cnt=0;
  }
};

node *root;
vector<node*> versions;
vector<int> input;
int N,C;

node* build(int i,int j){
  node *newNode = new node();
  if( i!=j ){
    int mid = ( i+j )>>1;
    newNode->l = build(i,mid);
    newNode->r = build(mid+1,j);
  }
  return newNode;
}

node* update(node *root,int i,int j,int pos){
  node *newNode = new node();
  newNode->l = root->l, newNode->r = root->r, newNode->cnt = root->cnt;
  if( i==j && i==pos ){
    newNode->cnt += 1;
    return newNode;
  }
  int mid=(i+j)>>1;
  if(pos<=mid) newNode->l = update(root->l,i,mid,pos);
  else newNode->r = update(root->r,mid+1,j,pos);
  newNode->cnt = newNode->l->cnt + newNode->r->cnt;
  return newNode;
}

int query(node *prev, node* curr,int i,int j,int val){
  if( prev->l == NULL ) return i;

  int lsum = curr->l->cnt - prev->l->cnt;
  int rsum = curr->r->cnt - prev->r->cnt;
  int mid = (i+j)>>1;
  if(lsum>val) return query(prev->l,curr->l,i,mid,val);
  else if(rsum>val) return query(prev->r,curr->r,mid+1,j,val);
  else return -1;
}

int main(){
  
  root=NULL;
  scanf("%d %d",&N,&C);
  input = vector<int>(N);
  root=build(1,C);
  versions.push_back(root);

  int ctr=0;
  for(int i=0;i<N;++i){
    scanf("%d",&input[i]);
    node *newRoot = update( versions[ctr],1,C,input[i]);
    versions.push_back(newRoot);
    ++ctr;
  }
  
  int Q;
  scanf("%d",&Q);
  for(int i=0;i<Q;++i){
    int u,v;
    scanf("%d %d",&u,&v);
    int freq = ((v-u+1)>>1);
    int pos = query(versions[u-1],versions[v],1,C,freq);
    if( pos == -1 ) printf("no\n");
    else printf("yes %d\n",pos);
  }

  return 0;
}
