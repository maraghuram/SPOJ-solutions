#include <cstdio>
#include <vector>
#include <queue>
const int MAX=20000;

using namespace std;


inline void fastRead_int(int &x) {
    register int c = getchar();
    x = 0;
    int neg = 0;

    for(; ((c<48 || c>57) && c != '-'); c = getchar());

    if(c=='-') {
    	neg = 1;
    	c = getchar();
    }

    for(; c>47 && c<58 ; c = getchar()) {
    	x = (x<<1) + (x<<3) + c - 48;
    }

    if(neg)
    	x = -x;
}

vector<int> visited,parent;
vector<char> character;

void print_rec(int node)
{
	if(node==-1) return;
	print_rec(parent[node]);
	putchar(character[node]);
}


void search(int n)
{
	queue<int> q;

	visited=vector<int>(MAX,0);
	parent=vector<int>(MAX,0);
	character=vector<char>(MAX,' ');
	parent[1]=-1;
	character[1]='1';
	visited[1]=1;

	q.push(1);

	while(!q.empty())
	{
		int rem;
		rem=q.front();
		q.pop();
		if(!rem)
		{
			print_rec(rem);
			putchar('\n');
			return;
		}

		int next=(rem*(10%n))%n;
		if(!visited[next])
		{
			parent[next]=rem;
			character[next]='0';
			visited[next]=1;
			q.push(next);
		}
		next=(next+1)%n;
		if(!visited[next])
		{
			parent[next]=rem;
			character[next]='1';
			visited[next]=1;
			q.push(next);
		}
	}


	printf("Impossible\n");
}

int main()
{
	int N,i;
	fastRead_int(N);
	for(int k=0;k<N;++k)
	{
		fastRead_int(i);
		search(i);
	}

	return 0;
}
