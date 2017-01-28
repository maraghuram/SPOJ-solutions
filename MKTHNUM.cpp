#include <bits/stdc++.h>
#define NMAX 111111
using namespace std;
typedef long long int ll;

struct node{
  node *l,*r;
  int cnt;
  node(){
    l=r=NULL;
    cnt=0;
  }
};

node *root;

int N,Q;
vector<ll> A,B;
vector<int> ranked;
vector<node*> ver;

node* build(int i,int j){
  node *newNode = new node;
  int mid=(i+j)>>1;
  if(i!=j){
    newNode->l = build(i,mid);
    newNode->r = build(mid+1,j);
  }
  return newNode;
}

node *update(node *curr,int i,int j,int pos){
  node *newNode = new node;
  newNode->l = curr->l, newNode->r = curr->r, newNode->cnt = curr->cnt;
  if(i==j && i==pos){
    newNode->cnt = 1;
    return newNode;
  }
  int mid=(i+j)>>1;
  if(pos<=mid) newNode->l = update(curr->l,i,mid,pos);
  else newNode->r = update(curr->r,mid+1,j,pos);
  newNode->cnt += 1;
  return newNode;
}

int query(node *left,node *right,int i_,int j_,int k_){  
  if(left->l==NULL) return i_;
  int lsum = right->l->cnt - left->l->cnt;
  int rsum = right->r->cnt - left->r->cnt;
  int mid_ = (i_+j_)>>1;
  //  cout<<i_<<","<<j_<<"--> "<<k_<<" "<<left->l->cnt<<" "<<right->l->cnt<<endl;
  if( k_ <= lsum ) return query(left->l,right->l,i_,mid_,k_);
  else return query( left->r, right->r, mid_ + 1, j_, k_ - lsum );
}

int main(){
  root=NULL;

  scanf("%d %d",&N,&Q);

  A=vector<ll>(N);  
  B=vector<ll>(N);
  root=build(1,N);
  assert(root!=NULL);
  
  ver.push_back(root);
  for(int i=0;i<N;++i){
    scanf("%lld",&A[i]);
    B[i]=A[i];
  }
  
  ranked=vector<int>(N);
  int currVer=0;
  sort(B.begin(),B.end());
  for(int i=0;i<N;++i) ranked[i] = lower_bound(B.begin(),B.end(),A[i]) - B.begin() + 1;
  for(int i=0;i<N;++i) {
    node * newRoot = update(ver[currVer],1,N,ranked[i]);
    ++currVer;
    ver.push_back(newRoot);    
    }

  for(int q=0;q<Q;++q) {
    int i,j,k;
    scanf("%d %d %d",&i,&j,&k);
    //    cout<< ver[i-1]->cnt << " " << ver[j]->cnt << endl;
    //    cout<<query( ver[i-1], ver[j], 1, N, k )<<endl;
    printf("%lld\n",B[ query( ver[i-1], ver[j], 1, N, k ) - 1 ] );
  }
  
  return 0;
}
