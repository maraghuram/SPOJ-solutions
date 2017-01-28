#include <cstdio>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

vector<vector<pair<int,int> > > graph;
const int MAX=INT_MAX;

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

inline void fastRead_string(char *str)
{
    register char c = 0;
    register int i = 0;

    while (c < 33)
        c = getchar();
    while (c != ' ' && c!='\n') {
        str[i] = c;
        c = getchar();
        i = i + 1;
    }
    str[i] = '\0';

}

int find_cost(int u,int v,int nodes)
{
	priority_queue< pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > Q;
	vector<int> visited=vector<int>(nodes+1,0);
	vector<int> costFound=vector<int>(nodes+1,MAX);

	for(int i=1;i<=nodes;++i)
		Q.push(pair<int,int>(MAX,i));

	Q.push(pair<int,int>(0,u));

	while(!Q.empty())
	{
		int node,cost;
		node=Q.top().second;
		cost=Q.top().first;

		Q.pop();

		if(visited[node]) continue;

		if(node==v)
			return cost;


		visited[node]=1;

		for(int i=0;i<(int)graph[node].size();++i)
		{
			int adj=graph[node][i].first;
			int ecost=graph[node][i].second;

			if(visited[adj]) continue;

			int currentcost=costFound[adj];

			if(currentcost>(cost+ecost))
			{
				costFound[adj]=cost+ecost;
				Q.push(pair<int,int>(cost+ecost,adj));
			}
		}
	}

	return 0;

}


int main()
{
	int T;
	fastRead_int(T);

	while(T>0)
	{
		int N,Q;
		char str[15];
		map<string,int> decode;

		fastRead_int(N);
		graph=vector<vector<pair<int,int> > >(N+1,vector<pair<int,int> >(0,pair<int,int>(0,0)));

		for(int i=1;i<=N;++i)
		{
			int neigh;

			fastRead_string(str);
			//scanf("%s",str);
			string s=string(str);
			decode.insert(pair<string,int>(s,i));

			fastRead_int(neigh);

			for(int j=0;j<neigh;++j)
			{
				int adj,cost;
				fastRead_int(adj);
				fastRead_int(cost);
				graph[i].push_back(pair<int,int>(adj,cost));
				graph[adj].push_back(pair<int,int>(i,cost));
			}
		}
		fastRead_int(Q);
		for(int i=0;i<Q;++i)
		{
			char s[15],d[15];
			fastRead_string(s);
			fastRead_string(d);
			//scanf("%s",s);
			//scanf("%s",d);
			string src=string(s);
			string dest=string(d);
			printf("%d\n",find_cost(decode[src],decode[dest],N));
		}

		--T;
	}


	return 0;
}
