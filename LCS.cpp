#include <bits/stdc++.h>
#define MAXLEN 555555
using namespace std;

struct state{
  int len,link;
  map<char,int> next;
};

state st[MAXLEN];
int sz,last;
int v,l,bestpos,best;

void sa_init(){
  sz=last=0;
  st[0].link=-1;
  st[0].len=0;
  ++sz;
}

void sa_extend(char c){
  int cur=sz++;
  st[cur].len=st[last].len+1;
  int p;
  for(p=last;p!=-1 && !st[p].next.count(c); p=st[p].link)
    st[p].next[c]=cur;
  if(p==-1)
    st[cur].link=0;
  else{
    int q=st[p].next[c];
    if(st[q].len== st[p].len+1)
      st[cur].link=q;
    else{
      int clone=sz++;
      st[clone].len=st[p].len+1;
      st[clone].next=st[q].next;
      st[clone].link=st[q].link;
      for(;p!=-1 && st[p].next[c]==q;p=st[p].link)
	st[p].next[c]=clone;
      st[q].link=st[cur].link=clone;
    }
  }
  last=cur;
}

string lcs(string s,string t){
  sa_init();
  for(int i=0;i<s.length();++i)
    sa_extend(s[i]);

  v=l=bestpos=best=0;
  for(int i=0;i<t.length();++i){
    while(v && !st[v].next.count(t[i])){
      v=st[v].link;
      l=st[v].len;
    }
    if(st[v].next.count(t[i])){
      v=st[v].next[t[i]];
      ++l;
    }
    if(l>best)
      best=l,bestpos=i;
  }
  return t.substr(bestpos-best+1,best);
}

int main(){
  char s[MAXLEN>>1],t[MAXLEN>>1];

  scanf("%s %s",s,t);
  
  lcs(string(s),string(t));
  
  printf("%d",best);
  
  return 0;
}
