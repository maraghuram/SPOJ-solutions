// author noob333
// H + Shift C + B + E + B + E

#include <bits/stdc++.h>
#define NMAX 111111
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
typedef vector<vector<int> > vvi;
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

int n;
vi prev;
ll sum[NMAX],dp[NMAX];
char buf[NMAX];

const ll MOD = 1000000007;

ll solve(string buf){
	n = sz(buf);
	prev = vi(26,0);
	memset(dp,0,sizeof(dp));
	memset(sum,0,sizeof(sum));
	REP(i,1,n+1){
		ll tmp = sum[i-1];
		if(prev[buf[i-1]-'A']) tmp = (tmp - sum[prev[buf[i-1]-'A']-1]+MOD)%MOD;
		else tmp++;

		prev[buf[i-1]-'A']=i;
		dp[i]=tmp;
		sum[i] = (sum[i-1]+tmp)%MOD;
	}
	sum[n] ++; sum[n] %= MOD;
	if(sum[n]<0) sum[n] += MOD;
	//printf("%lld\n",sum);
	return sum[n];
}

int main(){
	srand(time(NULL));
	int T;
	s(T);
	gets(buf);
	while(T--){
		gets(buf);
		string s=string(buf);
		printf("%lld\n",solve(s));
	}
	return 0;
}
