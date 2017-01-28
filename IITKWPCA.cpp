#include <bits/stdc++.h>
#define NMAX 11111
#define CMAX 55

using namespace std;

char buffer[NMAX];

inline int intOf( char c ){
  if( c>='a' && c<='z' ) return c-'a';
  return c-'A'+27;
}

struct node{
  node* link[CMAX];
  node(){
    for(int i=0;i<CMAX;++i) link[i]=NULL;
  }
};

node *root;

int check( string x ) {
  node *ptr = (root);
  for(int i=0;i<x.size();++i){
    if( ptr->link[intOf(x[i])] == NULL ) return 0;
    ptr = ptr->link[intOf(x[i])];
  }
  return 1;
}

void add( string x ) {
  node *ptr = (root);
  for(int i=0;i<x.size();++i){
    if( ptr->link[intOf(x[i])] == NULL ) 
      ptr->link[intOf(x[i])] = new node();
    ptr = ptr->link[intOf(x[i])];
  }
}

void getlineFast(){
  char c;
  int i=0;
  while((c=getchar_unlocked()) >0 ){
    if( c=='\n' ){
      buffer[i]='\0';
      break;
    }
    buffer[i++]=c;    
  }
}

int main(){
  int T;
  string s;
  scanf("%d",&T);
  getline(cin,s);
  while(T--){
    int count = 0;
    string line,x;
    root= new node();

    //    getlineFast();
    getline(cin,line);
    

    //    cout<<"Test : "<<T<<" "<<buffer<<endl;

    //line=string(buffer);
    stringstream ss(line);
    vector<string> words;
    
    while( ss >> x ) {
      assert( x.size() );
      //      string z;
      //      for(int j=x.size()-1;j>=0;--j) z.push_back(x[j]);
      words.push_back( x );
    }
    set<string> y;
    for(int i=0;i<words.size();++i){
      y.insert( words[i] );
      //      cout<< "Word "<<i<<" : "<<words[i]<<endl;
      /*      if( !check( words[i] ) ){
	++count;
	add( words[i] );
	//	cout<<" Added word : "<< words[i]<< endl;
	}*/
    }
    count = y.size();
    //    cout<<count<<endl;
    printf("%d\n",count);
    //    if ( T ) printf("\n");
  }

  return 0;
}
  printf("%d\n",count);
    //    if ( T ) printf("\n");
  }

  return 0;
}
