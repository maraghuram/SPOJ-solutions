#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long i64;
const int RMAX = 1000009;
const int NMAX = 1009;



struct Road { int u, v; };

struct sort_pred {
    bool operator()(const Road &left, const Road &right) {
        if(left.u<right.u) 	return true;
        if(left.u>right.u)	return false;

        if(left.v<right.v) 	return true;
        if(left.v>right.v)	return false;

        return false;
    }
};

i64 BIT[NMAX], m, n;
Road roads[RMAX];

i64 read(int idx) {
	i64 sum = 0;
	while(idx > 0) {
		sum += BIT[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void add(int idx, int v) {
	while(idx <= m) {
		BIT[idx] += v;
		idx += (idx & -idx);
	}
}

bool comp(const Road a, const Road b) {
	return ((a.u==b.u)? (a.v < b.v) : (a.u < b.u));
}

int main() {
	int t, k, i, j, cs = 1;
	i64 res;
	scanf("%d", &t);
	while(t--) {
		memset(BIT, 0, sizeof(BIT));
		res = 0;
		scanf("%d%d%d", &n, &m, &k);
		for(i = 0; i < k; i++) scanf("%d%d", &roads[i].u, &roads[i].v);
		sort(roads, roads + k, sort_pred());
		for(i = k-1; i >= 0; --i) {
			res += read(roads[i].v - 1);
			add(roads[i].v, 1);
			//printf("\n%d %d",roads[i].u,roads[i].v);
		}
		printf("Test case %d: %lld\n", cs++, res);
	}
	return 0;
}
