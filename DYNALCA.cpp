#include <bits/stdc++.h>
//#define debug 0
using namespace std;

struct node {
  node() : P(NULL), flip(0), pp(NULL) {
    C[0] = C[1] = NULL;
    fix();
  }
  node( int x ) {
    pp = P = NULL;
    C[0] = C[1] = NULL;
    flip = 0;
    val = x;
  }
  
  node* P;
  node* C[2];
  
  int val;
  int flip;
  node* pp;
  
/* Fix the parent pointers of our children. Additionally if we have any
 * extra data we're tracking (e.g. sum of subtree elements) now is the time to
* update them (all of the children will already be up to date). */
  void fix() {
    if(C[0]) C[0]->P = this;
    if(C[1]) C[1]->P = this;
  }
  
  /* Push the flip bit down the tree. */
  void push_flip() {
    if(!flip) return;
    flip = 0;
    swap(C[0], C[1]);
    if(C[0]) C[0]->flip ^= 1;
    if(C[1]) C[1]->flip ^= 1;
  }
  
  /* Return the direction of this relative its parent. */
  int up() {
    return !P ? -1 : (P->C[0] == this ? 0 : 1);
  }
  
  /* Simple zig step in the 'c' direction when we've reached the root. */
  void zig(int c) {
    node* X = C[c];
    if(X->P = P) P->C[up()] = X;
    C[c] = X->C[1 - c];
    X->C[1 - c] = this;
    fix(); X->fix();
    if(P) P->fix();
    swap(pp, X->pp);
  }
  
  /* Zig zig in the 'c' direction both times. */
  void zigzig(int c) {
    node* X = C[c];
    node* Y = X->C[c];
    if(Y->P = P) P->C[up()] = Y;
    C[c] = X->C[1 - c];
    X->C[c] = Y->C[1 - c];
    Y->C[1 - c] = X;
    X->C[1 - c] = this;
    fix(); X->fix(); Y->fix();
    if(P) P->fix();
    swap(pp, Y->pp);
  }
 
/* Zig zag first in the 'c' direction then in the '1-c' direciton. */
  void zigzag(int c) {
    node* X = C[c];
    node* Y = X->C[1 - c];
    if(Y->P = P) P->C[up()] = Y;
    C[c] = Y->C[1 - c];
    X->C[1 - c] = Y->C[c];
    Y->C[1 - c] = this;
    Y->C[c] = X;
    fix(); X->fix(); Y->fix();
    if(P) P->fix();
    swap(pp, Y->pp);
  }
 
  /* Splay this up to the root. Always finishes without flip set. */
  node* splay() {
    for(; P; ) {
      /* Reorganize flip bits so we can rotate as normal. */
      int c1 = up();
      int c2 = P->up();
      if(c2 == -1) {
	P->zig(c1);
      } else if(c1 == c2) {
	P->P->zigzig(c1);
      } else {
	P->P->zigzag(c2);
      }
    }
    return this;
  }
  
  /* Return the max element of the subtree rooted at this. */
  node* last() {
    push_flip();
    return C[1] ? C[1]->last() : splay();
  }
  
  /* Return the min element of the subtree rooted at this. */
  node* first() {
    push_flip();
    return C[0] ? C[0]->first() : splay();
  }
};

struct linkcut{
  linkcut(int N) {
    nodes.push_back( 0 );
    for(int i=0;i<N;++i) nodes.push_back( node(i+1) );
  }
  
  void link(int u, int v) {
    access( u );
    nodes[u].splay();
    access( v );
    nodes[v].splay();
    nodes[v].C[1] = &nodes[u];
    nodes[u].P = &nodes[v];
  }
  
  void cut(int u) {
    access(u);
    nodes[u].splay();
    assert( nodes[u].C[0] );
    if( nodes[u].C[0] ){
      nodes[u].C[0]->P = NULL;
      nodes[u].C[0]->pp = NULL;
      nodes[u].C[0] = NULL;
    }
  }
  
  /* Move u to root of represented tree. */
  void make_root(int u) {
    access(u);
    nodes[u].splay();
    if(nodes[u].C[0]) {
      nodes[u].C[0]->P = NULL;
      nodes[u].C[0]->flip ^= 1;
      nodes[u].C[0]->pp = &nodes[u];
      
      nodes[u].C[0] = NULL;
      nodes[u].fix();
    }
  }
  

  /* Move u to root aux tree. Return the root of the root aux tree. */
  node* access(int u) {
    node* x,* pp;
    x = nodes[u].splay();
    if( x->C[1] ){
      x->C[1]->pp = x;
      x->C[1]->P = NULL;
    }
    x->C[1] = NULL;
    for(; x->pp; x = pp) {
      pp = x->pp->splay();
      x->pp = NULL;
      if(pp->C[1]) {
  	pp->C[1]->P = NULL;
  	pp->C[1]->pp = pp;
      }
      pp->C[1] = x;
      pp->fix();
    }
    return x;
  }

  // void link(int u, int v) {
  //   make_root(v);
  //   nodes[v].pp = &node[u];
  // }
  
  // node* access( int u ){
  //   node *x, *ptr, *last;
  //   x = &nodes[u];
  //   x->splay();
  //   if( x->C[1] ) x->C[1]->P = NULL, x->C[1]->pp = x;
  //   x->C[1] = NULL;
  //   ptr = x;
  //   last = NULL;
  //   while( ptr->pp ){
  //     node *w= ptr->pp;
  //     w->splay();
  //     if( w->C[1] ) w->C[1]->P = NULL, w->C[1]->pp = w;
  //     w->C[1] = ptr;
  //     ptr->P = w;
  //     ptr->pp = NULL;
  //     last = ptr;
  //     ptr = w;
  //   }
  //   return ptr;
  // }

  int lca( int u, int v ) {
    //    cout<<" lca begin"<<endl;
    access( u );
    nodes[u].splay();
    node *temp = access( v );
    nodes[v].splay();
    //    cout<<" lca end"<<endl;
    return temp->val;

  }


  
  vector<node> nodes;
};

#ifdef debug
void solve1(){
  int N,Q;
  scanf("%d %d",&N,&Q);
  
 linkcut lcTree(N);

  char str[5];
  int u,v;
  for(int i=0;i<Q;++i){
    scanf("%s",str);
    if( str[0] == 'c' ){
      scanf("%d",&u);
      lcTree.cut( u );
    }
    else if( str[1] == 'c' ){
      scanf("%d %d",&u,&v);
      printf("%d\n",lcTree.lca(u,v) );
    }
    else{
      scanf("%d %d",&u,&v);
      lcTree.link(u,v);
    }
  }
 
}
#endif

#ifndef debug
int main(){
  int N,Q;
  scanf("%d %d",&N,&Q);

 linkcut lcTree(N);

  char str[5];
  int u,v;
  for(int i=0;i<Q;++i){
    scanf("%s",str);
    if( str[0] == 'c' ){
      scanf("%d",&u);
      lcTree.cut( u );
    }
    else if( str[1] == 'c' ){
      scanf("%d %d",&u,&v);
      printf("%d\n",lcTree.lca(u,v) );
    }
    else{
      scanf("%d %d",&u,&v);
      lcTree.link(u,v);
    }
  }
 
  return 0;
}
#endif
