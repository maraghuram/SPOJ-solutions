#include <bits/stdc++.h>
#define NMAX 30
using namespace std;
typedef pair<int,int> pi;
typedef vector<pi> vp;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef long long int ll;

int k,p;
vvi graph(8,vi(3));
vp nodes;

vvi matrixMul(vvi a,vvi b){
  if(a[0].size()!=b.size()){
    cout << a[0].size() << " " << b.size();
    assert(0);
  }
  vvi res(a.size(),vi(b[0].size()));
  ll tmp;
  for(int i=0;i<a.size();++i){
    for(int j=0;j<b[0].size();++j){
      tmp=0;
      for(int k=0;k<b.size();++k){
	tmp += (ll(a[i][k])*b[k][j])%p;
	tmp %= p;
      }
      res[i][j]=tmp;
    }
  }
  return res;
}

vvi matrixPow(vvi a,int pw){
  vvi res=vvi(a);
  --pw;
  while(pw>0){
    if(pw&1) res=matrixMul(res,a);
    pw >>=1 ; a=matrixMul(a,a);
  }
  return res;
}

vvi build(){
  vvi ant(24,vi(24,0));
  graph[0][0]=1;graph[0][1]=3;graph[0][2]=4;
  graph[1][0]=0;graph[1][1]=2;graph[1][2]=5;
  graph[2][0]=1;graph[2][1]=3;graph[2][2]=6;
  graph[3][0]=0;graph[3][1]=2;graph[3][2]=7;
  graph[4][0]=0;graph[4][1]=5;graph[4][2]=7;
  graph[5][0]=1;graph[5][1]=4;graph[5][2]=6;
  graph[6][0]=2;graph[6][1]=5;graph[6][2]=7;
  graph[7][0]=3;graph[7][1]=4;graph[7][2]=6;

  for(int i=0;i<8;++i){
    nodes.push_back(pi(i,graph[i][0]));
    nodes.push_back(pi(i,graph[i][1]));
    nodes.push_back(pi(i,graph[i][2]));
  }

  for(int i=0;i<24;++i)
    for(int j=0;j<24;++j)
      if(i!=j && nodes[i].first!=nodes[j].first &&nodes[i].second!=nodes[j].first){
	for(int k=0;k<3;++k)
	  if(nodes[j].first==graph[nodes[i].first][k] && nodes[j].second==nodes[i].first){
	    //cout << nodes[i].first <<"-"<< nodes[i].second << " " << nodes[j].first << "-" << nodes[j].second << endl;
	    ant[i][j]=1; break;
	  }
      }
  
  return ant;
}

int main(){
  char str[10];
  int st,en;
  ll res=0;

  gets(str);
  scanf("%d %d",&k,&p);
  vvi adj=build();

  // for(int i=0;i<adj.size();++i){
  //   for(int j=0;j<adj[i].size();++j)
  //     cout << adj[i][j] << " ";
  //   cout << endl;
  // }


  st=str[0]-'A';
  en=str[2]-'A';

  if(k==1){
    if(graph[st][0]==en || graph[st][1]==en || graph[st][2]==en)
      printf("1\n");
    else
      printf("0\n");
  }

  if(k>1){
    adj=matrixPow(adj,k-1);    
    for(int i=0;i<3;++i){
      int u=lower_bound(nodes.begin(),nodes.end(),pi(graph[st][i],st))-nodes.begin();
      for(int j=0;j<3;++j){
	int v=lower_bound(nodes.begin(),nodes.end(),pi(en,graph[en][j]))-nodes.begin();
	res+=adj[u][v]; res %= p;
      }
    }
    printf("%lld\n",res);
  }

  return 0;
}
