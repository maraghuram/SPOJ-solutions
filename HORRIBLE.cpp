#include <stdio.h>
using namespace std;
 
#define L(x) (1 + ((x) << 1))
#define R(x) (2 + ((x) << 1))
typedef unsigned long long i64;
int const MAXN = 100000 + 2;
 
struct node {
    node() {}
    node(int b, int e, int m, i64 v)
        : begin(b), end(e), mid(m), value(v) {}
    int begin, end, mid;
    i64 value, add_value;
};
 
struct segment_tree {
    node tree[MAXN << 2];
 
    void init_tree(int index, int left, int right) {
        node& now = tree[index];
        now.begin = left, now.end = right;
        now.mid = (now.begin + now.end) >> 1;
        if (now.begin != now.end) {
            init_tree(L(index), left, now.mid);
            init_tree(R(index), now.mid + 1, right);
            now.value = now.add_value = 0;
        } else
            now.value = now.add_value = 0;
    }
 
    i64 get_value(int index) {
        node& now = tree[index];
        return now.value + (now.add_value * (i64) (now.end - now.begin + 1));
    }
 
    void broadcast_value(int index) {
        tree[L(index)].add_value += tree[index].add_value;
        tree[R(index)].add_value += tree[index].add_value;
        tree[index].add_value = 0;
    }
 
    void update(int index, int left, int right, int value) {
        node& now = tree[index];
        if (now.begin >= left && now.end <= right) {
            now.add_value += value;
            return;
        }
        if (now.begin > right || now.end < left)
            return;
        if (now.begin < left || now.end > right) {
            broadcast_value(index);
            update(L(index), left, right, value);
            update(R(index), left, right, value);
            now.value = get_value(L(index)) + get_value(R(index));
        }
    }
 
    i64 query(int index, int left, int right) {
        node& now = tree[index];
        if (now.begin >= left && now.end <= right)
            return get_value(index);
        if (now.begin > right || now.end < left)
            return 0;
        i64 result = 0;
        if (now.begin < left || now.end > right) {
            broadcast_value(index);
            result = query(L(index), left, right) + query(R(index), left, right);
            now.value = get_value(L(index)) + get_value(R(index));
        }
        return result;
    }
};
 
segment_tree tree;
 
int main(int argc, char **args) {
    int TC, p, q, v; scanf("%d", &TC);
    while (TC-- > 0) {
        int n; scanf("%d", &n);
        int c; scanf("%d", &c);
        tree.init_tree(0, 0, n - 1);
        for (int i = 0; i < c; ++i) {
            scanf("%d", &n);
            if (n == 0) {
                scanf("%d%d%d", &p, &q, &v);
                tree.update(0, p - 1, q - 1, v);
            } else {
                scanf("%d%d", &p, &q);
                printf("%lld\n", tree.query(0, p - 1, q - 1));
            }
        }
    }
    return 0;
}"%d%d%d", &p, &q, &v);
                tree.updateTree(tuple(p,q),1, v);
            } else {
                scanf("%d%d", &p, &q);
                printf("%llu\n", tree.queryTree(tuple(p,q),1));
            }
        }
    }
/*

	SegmentTree t(10);

	t.printTree(1);
	printf("\n");
	t.updateTree(tuple(5,8),1,50);
	t.printTree(1);
	printf("\n");
	printf("\n\n%llu\n",t.queryTree(tuple(4,10),1));
	t.printTree(1);


	printf("\n1\n1000 100000");

	for(int i=0;i<100000;++i)
		printf("\n0 1 1000 50");
		*/
    return 0;
}
