#include <bits/stdc++.h>
#define NMAX 55555
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)

using namespace std;
struct node{
  string x;
  int y;
  node(string x,int y){
    this->x=x;this->y=y;
  }
};

vector<int> pri;
vector<node> input;
int tree[NMAX<<2];
int N;

inline node parseString(string x){
  int res=0;
  string label;

  int i;
  for(i=0;x[i]!='/';++i) label.push_back(x[i]);
  for(++i;i<x.size();++i){
    res+=(x[i]-'0');
    res*=10;
  }
  res/=10;
  return node(label,res);
}

bool cmp(node lhs,node rhs){ return (lhs.x<rhs.x); }

int merge(int y,int z){
  if(input[y-1].y>input[z-1].y) return y;
  return z;
}

void build(int index,int i,int j){
  if(i==j){    
    tree[index]=i;
    return;
  }
  int mid=(i+j)>>1;
  build(L(index),i,mid);
  build(R(index),mid+1,j);
  tree[index]=merge(tree[L(index)],tree[R(index)]);
}

int query(int index,int i,int j,int left,int right){
  if(i==left && j==right) return tree[index];
  int mid=(i+j)>>1;
  if(right<=mid) return query(L(index),i,mid,left,right);
  else if(left>mid) return query(R(index),mid+1,j,left,right);
  return merge(query(L(index),i,mid,left,mid),query(R(index),mid+1,j,mid+1,right));
}

void solve(int left,int right){
  if(left>right) return;
  if(left==right){
    cout<<"("<<input[left-1].x<<"/"<<input[left-1].y<<")";
    return;
  }

  int m=query(1,1,N,left,right);
  cout<<"(";
  solve(left,m-1);
  cout<<input[m-1].x<<"/"<<input[m-1].y;
  solve(m+1,right);
  cout<<")";
}

int main(){
  while(1){
    cin>>N;
    if(N==0) break;
    
    input.clear();
    for(int i=0;i<N;++i){
      string x;
      cin>>x;
      node tmp=parseString(x);
      input.push_back(tmp);
    }

    sort(input.begin(),input.end(),cmp);
    build(1,1,N);
    solve(1,N);
    cout<<endl;
  }
  return 0;
}
