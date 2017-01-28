// author noob333
// H + Shift C + B + E + B + E

#include <bits/stdc++.h>
#define NMAX 55
#define TMAX 1111
//#define DEBUG 1
using namespace std;
// Input macros
#define s(n)                        scanf("%d",&n)
#define sc(n)                       scanf("%c",&n)
#define sl(n)                       scanf("%lld",&n)
#define sf(n)                       scanf("%lf",&n)
#define ss(n)                       scanf("%s",n)

// Useful constants
#define INF                         (int)1e9
#define EPS                         1e-9
#define DINF                        2.0e7

// Useful hardware instructions
#define bitcount                    __builtin_popcount
#define gcd                         __gcd

// Useful container manipulation / traversal macros
#define REP(i,a,b)                  for(int i=a;i<b;i++)
#define RREP(i,a,b)                 for(int i=a;i>b;i--)
#define foreach(v, c)               for( typeof( (c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define all(a)                      a.begin(), a.end()
#define in(a,b)                     ( (b).find(a) != (b).end())
#define pb                          push_back
#define fill(a,v)                    memset(a, v, sizeof a)
#define sz(a)                       ((int)(a.size()))
#define mp                          make_pair
#define fi                          first
#define se                          second

// Some common useful functions
#define sq(a)                        ( (a)*(a) )
#define maX(a,b)                     ( (a) > (b) ? (a) : (b))
#define miN(a,b)                     ( (a) < (b) ? (a) : (b))
#define checkbit(n,b)                ( (n >> b) & 1)
#define setbit(n,b)                  ( n |= (1<<b) )
#define unsetbit(n,b)                ( n &= ~(1<<b) )
#define DREP(a)                      sort(all(a)); a.erase(unique(all(a)),a.end())
#define INDEX(arr,ind)               (lower_bound(all(arr),ind)-arr.begin())


typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef set<int> si;
typedef map<string, int> msi;

#ifdef DEBUG
     #define debug(args...)            {dbg,args; cerr<<endl;}
#else
    #define debug(args...)              // Just strip off all debug tokens
#endif

struct debugger
{
    template<typename T> debugger& operator , (const T& v)
    {    
        cerr<<v<<" ";    
        return *this;    
    }
} dbg;

template <typename T1, typename T2>
    inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p)
    {
        return os << "(" << p.first << ", " << p.second << ")";
    }

    template<typename T>
    inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v)
    {
        bool first = true;
        os << "[";
        for(unsigned int i = 0; i < v.size(); i++)
        {
            if(!first)
                os << ", ";
            os << v[i];
            first = false;
        }
        return os << "]";
    }

    template<typename T>
    inline std::ostream &operator << (std::ostream & os,const std::set<T>& v)
    {
        bool first = true;
        os << "[";
        for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
        {
            if(!first)
                os << ", ";
            os << *ii;
            first = false;
        }
        return os << "]";
    }

    template<typename T1, typename T2>
    inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v)
    {
        bool first = true;
        os << "[";
        for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
        {
            if(!first)
                os << ", ";
            os << *ii ;
            first = false;
        }
        return os << "]";
    }

int dt[NMAX][NMAX],ti[NMAX][NMAX],n,t;
ii dp[NMAX][TMAX];

ii solve(int curr,int tl){
  debug(curr,tl);
  if(tl<0) return ii(INF,INF);
  if(dp[curr][tl].fi!=INF) return dp[curr][tl];
  if(curr==n-1) return dp[curr][tl]=ii(0,0);

  ii ans(INF,INF);
  REP(i,0,n){
    if(i!=curr){
      ii tmp=solve(i,tl-ti[curr][i]);
      if(tmp.fi+dt[curr][i]<ans.fi)
	ans=ii(tmp.fi+dt[curr][i],tmp.se+ti[curr][i]);
    }
  }
  return dp[curr][tl]=ans;
}

int main(){
  while(1){
  s(n); s(t);
  if(n==0 && t==0) break;
  REP(i,0,n){
    REP(j,0,n){
      s(ti[i][j]);
    }
  }
  REP(i,0,n){
    REP(j,0,n){
      s(dt[i][j]);
    }
  }
  REP(i,0,n){
    REP(j,0,t+2){
      dp[i][j]=ii(INF,INF);
    }
  }
    
  ii res=solve(0,t);
  printf("%d %d\n",res.fi,res.se);

  
  }
  return 0;
}
