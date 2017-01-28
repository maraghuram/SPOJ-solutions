#include <bits/stdc++.h>
#define NMAX 8888

using namespace std;
struct node{
  node *left,*right;
  int val;
  node(int x){
    left=right=NULL;
    val=x;
  }	
};

node *root;
int preOrder[NMAX],postOrder[NMAX],inOrder[NMAX];
int pos[NMAX];
int ctr;

node* split(int i, int j){  
  if(i>j) return NULL;
  int x=preOrder[ctr++];
  node *newNode=new node(x);
  
  if(i==j) return newNode;

  int mid = pos[x];
  newNode->left = split(i,mid-1);
  newNode->right= split(mid+1,j);
  return newNode;
}

int verify(node *root){
    if( root==NULL ) return 1;
    if( !verify(root->left) || !verify(root->right) ) return 0;
    //cout<<postOrder[ctr++]<<endl;
    //return 1;
    return postOrder[ctr++] == root->val;
}

void print(node *root){
  if(root==NULL) return;
  print(root->left);print(root->right);
  cout<<root->val<<endl;
}

int main(){
  int N;
  root=NULL;
  cin>>N;

  for(int i=0;i<N;++i) cin>>preOrder[i];
  for(int i=0;i<N;++i) cin>>postOrder[i];
  for(int i=0;i<N;++i){
    cin>>inOrder[i];
    pos[inOrder[i]]=i;
  }

  ctr=0;
  root=split(0,N-1);
  ctr=0;
  if( verify(root) ) cout<<"yes"<<endl;
  else cout<<"no"<<endl;  
  //print(root);
  return 0;
}