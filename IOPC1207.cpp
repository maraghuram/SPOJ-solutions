
// author noob333
// H + Shift C + B + E + B + E

#include <bits/stdc++.h>
#define NMAX 111111
#define DEBUG 1
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
#define L(x)						(x<<1)
#define R(x)						((x<<1)+1)
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



struct segNode{
	int lazy;
	int sum,len;
	segNode(int a=0,int b=0,int c=0){
		lazy=a;
		sum=b; len=c;
	}
};

struct segTree{
	segNode tree[NMAX<<2];

	void modify(int index,int val){
		if(val%2) tree[index].sum = tree[index].len-tree[index].sum;
		tree[index].lazy += val;
	}

	void push(int index,int i,int j){
		if(i!=j){
			if(tree[index].lazy){
				modify(L(index),tree[index].lazy);
				modify(R(index),tree[index].lazy);
				tree[index].lazy=0;
			}
		}
	}

	void build(int index,int i,int j){
		tree[index]=segNode(0,0,j-i+1);
		if(i==j) return;
		int mid=(i+j)>>1;
		build(L(index),i,mid);
		build(R(index),mid+1,j);
	}

	void update(int index,int i,int j,int st,int en){
		if(i==st && j==en){
			modify(index,1);
			return;
		}
		push(index,i,j);
		int mid = (i+j)>>1;
		if(en<=mid) update(L(index),i,mid,st,en);
		else if(st>mid) update(R(index),mid+1,j,st,en);
		else{
			update(L(index),i,mid,st,mid);
			update(R(index),mid+1,j,mid+1,en);
		}
		tree[index].sum = tree[L(index)].sum + tree[R(index)].sum;
	}

	int query(int index,int i,int j,int st,int en){
		if(i==st && j==en)	return tree[index].sum;
		push(index,i,j);
		int mid = (i+j)>>1;
		int x1,x2;
		x1=x2=0;

		if(en<=mid) x1=query(L(index),i,mid,st,en);
		else if(st>mid) x2=query(R(index),mid+1,j,st,en);
		else{
			x1=query(L(index),i,mid,st,mid);
			x2=query(R(index),mid+1,j,mid+1,en);
		}
		//tree[index].sum = tree[L(index)].sum + tree[R(index)].sum;
		return x1+x2;
	}

	void printTree(int index,int i,int j){
		if(i==j){
			printf("%d,%d - %d %d %d\n",i,j,tree[index].lazy,tree[index].sum,tree[index].len);
			return;
		}
		int mid=(i+j)>>1;
		printTree(L(index),i,mid);
		printTree(R(index),mid+1,j);
		printf("%d,%d - %d %d %d\n",i,j,tree[index].lazy,tree[index].sum,tree[index].len);
	}

}segTrees[3];
int N[3];

void init(){
	REP(i,0,3){
		fill(segTrees[i].tree,0);
		segTrees[i].build(1,0,N[i]-1);
	}
}

void change(int ind,int u,int v){
	segTrees[ind].update(1,0,N[ind]-1,u,v);
	//segTrees[ind].printTree(1,0,N[ind]-1);
	//cout << endl;
}

ll ask(int x1,int y1,int z1,int x2,int y2,int z2){
	ll r1=segTrees[0].query(1,0,N[0]-1,x1,x2);
	ll r2=segTrees[1].query(1,0,N[1]-1,y1,y2);
	ll r3=segTrees[2].query(1,0,N[2]-1,z1,z2);
	ll g1=(x2-x1+1)-r1;
	ll g2=(y2-y1+1)-r2;
	ll g3=(z2-z1+1)-r3;
	//debug(r1,g1,r2,g2,r3,g3);
	return (r1*r2*r3+r1*g2*g3+g1*r2*g3+g1*g2*r3);
}

void solve(){
	int x1,x2,y1,y2,z1,z2;
	int Q;

	REP(i,0,3)
		s(N[i]);

	init();
	s(Q);

	REP(i,0,Q){
		int ty;
		s(ty);
		if(ty==3){
			s(x1); s(y1); s(z1);
			s(x2); s(y2); s(z2);
			printf("%lld\n",ask(x1,y1,z1,x2,y2,z2));
		}
		else{
			s(x1); s(x2);
			change(ty,x1,x2);
		}
	}
}

int main(){
	//freopen("1.in","r",stdin);
	int T;
	s(T);
	while(T--){
		solve();
	}
	//fclose(stdin);
	return 0;
}
