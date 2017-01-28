#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define edge pair< int, int >
#define MAX 1001

// ( w (u, v) ) format
vector< pair< int, edge > > GRAPH, MST;
map<int,int> parent;
int total, N, E;

int findset(int x)
{
    if(x != parent[x])
        parent[x] = findset(parent[x]);
    return parent[x];
}

void kruskal()
{
    int i, pu, pv;
    sort(GRAPH.begin(), GRAPH.end()); // increasing weight
    for(i=total=0; i<E; i++)
    {
        pu = findset(GRAPH[i].second.first);
        pv = findset(GRAPH[i].second.second);
        if(pu != pv)
        {
            MST.push_back(GRAPH[i]); // add to tree
            total += GRAPH[i].first; // add edge cost
            parent[pu] = parent[pv]; // link
        }
    }
}

void reset()
{
    // reset appropriate variables here
    // like MST.clear(), GRAPH.clear(); etc etc.
	GRAPH.clear();
	MST.clear();
    for(int i=1; i<=N; i++) parent[i] = i;
}

void print()
{
    int i, sz;
    // this is just style...
    sz = MST.size();
/*    for(i=0; i<sz; i++)
    {
        printf("( %d", MST[i].second.first);
        printf(", %d )", MST[i].second.second);
        printf(": %d\n", MST[i].first);
    }
    */
    printf("%d\n", total);
}

int main()
{
    int i, u, v, w,T;
    char str[15];

    scanf("%d",&T);

    while(T>0)
    {

    scanf("%d",&N);
    reset();
    E=0;
    for(i=1;i<=N;++i)
    {
    	int t;

    	u=i;
    	scanf("%s",str);
    	scanf("%d",&t);
    	E+=t;
    	for(int j=1;j<=t;++j)
    	{
    		scanf("%d %d",&v,&w);
    		GRAPH.push_back(pair<int,edge>(w,edge(u,v)));
    	}
    }

    kruskal();
    print();
    --T;
    }

    return 0;
}
