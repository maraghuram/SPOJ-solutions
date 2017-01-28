#include <iostream>
#include <algorithm>
#include <cstdio>
#define NMAX 111111
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)
using namespace std;

int getint()
{
    char c;
    while (!isdigit(c = getchar()));
    int ret = c - 48;
    while (isdigit(c = getchar()))
        ret = ret * 10 + c - 48;
    return ret;
}

template <typename Titem>
class AVLTree{
public:
  class Tnode{
  public:
    Titem item;
    Tnode *left, *right;
    int height; int sz; int cnt;
    Tnode(Titem x, Tnode* l=NULL, Tnode* r=NULL){
      item=x; left=l; right=r; height=1; sz=1; cnt=1;
    }
  };

  Tnode* root;
  int size;

  AVLTree(){
    root = NULL; size = 0;
  }

  int getHeight(Tnode* n){
    if(n==NULL) return 0;
    else return n->height;
  }

  int getSz(Tnode* x){
    if(x==NULL) return 0;
    else return x->sz;
  }


  Tnode* setHeight(Tnode *x){
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
  }

  Tnode* setSz(Tnode *x){
    x->sz=x->cnt;
    x->sz += getSz(x->left); x->sz += getSz(x->right);
    return x;
  }

  Tnode* SRR(Tnode *x){
    Tnode* k = x->left;
    x->left = k->right;
    k->right = x;
    x = setHeight(x);
    x = setSz(x);
    k = setHeight(k);
    k = setSz(k);
    return k;
  }

  Tnode* SLR(Tnode *x){
    Tnode* k = x->right;
    x->right = k->left;
    k->left = x;
    x = setHeight(x);
    x = setSz(x);
    k = setHeight(k);
    k = setSz(k);
    return k;
  }

  Tnode* DRR(Tnode *x){
    x->left = SLR(x->left);
    x = SRR(x);
    return x;
  }
  
  Tnode* DLR(Tnode *x){
    x->right = SRR(x->right);
    x = SLR(x);
    return x;
  }  

  Tnode* balance(Tnode* n)
  {
    if (getHeight(n->left) - getHeight(n->right) > 1) n = balRight(n);
    else if (getHeight(n->right) - getHeight(n->left) > 1) n = balLeft(n);
    return n;
  }

  Tnode* balRight (Tnode* n)
  {
    if ((getHeight(n->left->right)) > (getHeight(n->left->left))) 
      {n = DRR(n);
        return n;}
    else
      {n = SRR(n);
        return n;}
  }

  Tnode* balLeft (Tnode* n)
  {
    if ((getHeight(n->right->left)) > (getHeight(n->right->right)))
      n = DLR(n);
    else
      n = SLR(n);
    return n;
  }

  Tnode* insert(Tnode *x, Titem item){
    if(x==NULL){
      ++size;
      return new Tnode(item);
    }
    if(x->item == item ){
      return x;
    }

    if(x->item < item ) x->right = insert(x->right,item);
    else x->left = insert(x->left,item);

    x = setHeight(x);
    x = setSz(x);
    x = balance(x);
    return x;
  }

  Tnode* remove (Tnode* n, Titem item)
  {
    if (n == NULL) // got down to the end without finding the object to be removed
      {
        return NULL; // CHANGED FROM NULL
      } // item not found
    if (n->item == item) // item found at current Tnode
      {
        if (getHeight(n) == 1) // leaf Tnode    
          {
            // "BSTremove: leaf Tnode" << endl;
            delete n;
            size--; // remove a Tnode from the tree
            return NULL;
          }
        else if ((n->right == NULL)&&(n->left != NULL)) // left child only
          {
            size--;
            Tnode* temp = n;
            n = n->left;
            delete (temp);
            return n;
          }
        else if ((n->left == NULL)&&(n->right != NULL)) // right child only
          {
            size--;
            Tnode* temp = n;
            n = n->right;
            delete (temp);
            return n;
          }
        else if ((n->left != NULL)&&(n->right != NULL)) // two children
          {
            Tnode *temp = findMin(n->right);
            n->item = temp->item; // set the current Tnode to contain that smallest item
	    n->cnt = temp->cnt;
            n->right = remove (n->right, temp->item);
          } // remove the smallest item from the right subtree
      }       
    else if (n->item < item) // the item we are looking for is bigger than the one in the current Tnode
      n->right = remove (n->right, item);// remove from the right subtree
    else if (n->item >= item)
      n->left = remove (n->left, item); // remove from left subtree
    n = setHeight(n);
    n = setSz(n);
    n = balance(n);
    return n;
  }

  Tnode* findMin(Tnode* n)
  {
    // find the smallest thing in this subtree
    if (n->left == NULL) // gone down as far as possible
      return n;
    else
      return findMin(n->left); // go left
  }

  Tnode* findNode(Tnode *n, Titem item){
    if(n==NULL) return NULL;
    if(n->item==item) return n;
    if(n->item < item) return findNode(n->right,item);
    return findNode(n->left,item);
  }

  Tnode* update(Tnode* x,Titem item,int val){
    if(x==NULL) return NULL;
    x->sz+=val;
    if(x->item==item){
      x->cnt+=val;
      return x;
    }
    if(x->item<item) x->right=update(x->right,item,val);
    else x->left=update(x->left,item,val);
    return x;
  }

  void add(Titem item){
    Tnode *tmp=NULL;
    if(size==0){
      root=new Tnode(item);
      size++;
      return;
    }
    if((tmp=findNode(root,item))!=NULL) root=update(root,item,1);
    else root=insert(root,item);
  }

  void del(Titem item){
    if(size==0) return;

    Tnode *tmp=findNode(root,item);
    if(tmp!=NULL){
      if(tmp->cnt==1) root=remove(root,item);
      else root=update(root,item,-1);
    }
  }

  int findRank(Titem item){
    Tnode* ptr=root;
    int val=0;
    while( ptr ){
      if(ptr->item == item ){
	val += ptr->cnt;
	val += getSz(ptr->left);
	return val;
      }
      else if(ptr->item >item ) ptr = ptr->left;
      else{
	val += ptr->cnt;
	val += getSz(ptr->left);
	ptr = ptr->right;
      }
    }

    return val;
  }
  
  void printTree(Tnode* root){
    if(!root) return;
    cout << root->item << "-" << root->height <<" " << root->sz <<" "<<root->cnt<<endl;
    printTree(root->left);
    printTree(root->right);
  }

};



struct node{
  AVLTree<int> val;
  node(){
    val=AVLTree<int>();
  }
}tree[NMAX<<2];

int N,M;
int A[NMAX];

void build(int index,int i,int j){
  for(int a=i;a<=j;++a) tree[index].val.add(A[a-1]);
  if(i<j){
    int mid=(i+j)>>1;
    build(L(index),i,mid);
    build(R(index),mid+1,j);
  }
}

void update(int index,int i,int j,int pos,int value){
  tree[index].val.del(A[pos-1]);
  tree[index].val.add(value);
  if(i<j){
    int mid=(i+j)>>1;
    if( pos<=mid ) update(L(index),i,mid,pos,value);
    else update(R(index),mid+1,j,pos,value);
  }
}

int query(int index,int i,int j,int st, int en,int X){
  if( i==st && j==en ) return tree[index].val.findRank(X);
  
  int mid = ( i + j ) >> 1;
  if( en <= mid ) return query( L(index), i , mid, st, en, X );
  else if( st > mid ) return query( R(index), mid+1, j,st,en,X);
  else return ( query(L(index),i,mid,st,mid,X)+ query(R(index),mid+1,j,mid+1,en,X));
}

void printTree(int index,int i,int j){
  if(i==j){
    cout << "(" << i << "," << j << ")" << endl;
    tree[index].val.printTree(tree[index].val.root);
    return;
  }
  int mid=(i+j)>>1;
  printTree(L(index),i,mid);
  printTree(R(index),mid+1,j);
  cout << "(" << i << "," << j << ")" << endl;
  tree[index].val.printTree(tree[index].val.root);
}

void debug(){
  cout << "------------------" << endl;
  printTree(1,1,N);
  cout << "------------------" << endl;
}

int main(){
  N=getint(); M=getint();
  //scanf("%d %d",&N,&M);
  for(int i=0;i<N;++i){
    //scanf("%d",&A[i]);
    A[i]=getint();
  }

  build(1,1,N);
  //debug();

  for(int i=0;i<M;++i){
    char buf[3];
    int u,v,w;
    scanf("%s",buf);
    if( buf[0] == 'C' ){
      scanf("%d %d %d",&u,&v,&w);
      printf("%d\n",query(1,1,N,u,v,w));
    }
    else{
      scanf("%d %d",&u,&v);
      update(1,1,N,u,v);
      A[u-1]=v;
      //debug();
    }
  }

  return 0;
}
