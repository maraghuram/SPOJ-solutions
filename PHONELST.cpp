#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MAX=10005;

struct Node
{
	int prefixes;
	int words;
	vector<Node*> links;

	Node()
	{
		prefixes=words=0;
		links.resize(10,NULL);
	}
};

class Trie
{
	Node *root;
	int count;

public:
	Trie()
	{
		root=new Node();
		count=1;
	}

	int countPrefixes(const string& s) const;
	void insert(const string s);


};

int Trie::countPrefixes(const string& s) const{
    int len = s.size();
    Node* t = root;

    for(int k=0;k<len;++k){
        if(t->links[s[k]-'0']==NULL) return 0;
        t = t->links[s[k]-'0'];
    }

    return t->prefixes;
}

void Trie::insert(const string s){
    int len = s.size();
    Node* t = root;

    for(int k=0;k<len;++k){
	    if(t->links[s[k]-'0']==NULL){
	        t->links[s[k]-'0'] = new Node();
	        ++count;
	    }
	    t = t->links[s[k]-'0'];
	    ++(t->prefixes);
    }

    ++(t->words);
}

int main()
{
	int T;

	scanf("%d",&T);
	while(T>0)
	{
		int N;
		string numbers[MAX];
		char input[15];
		scanf("%d",&N);
		for(int i=0;i<N;++i)
		{
			scanf("%s",input);
			numbers[i]=string(input);
		}

		sort(numbers,numbers+N);

		Trie *t;
		t=new Trie();
		bool flag=true;

		for(int i=N-1;i>=0 && flag;--i)
		{
			t->insert(numbers[i]);
			if(t->countPrefixes(numbers[i])>1)	flag=false;
		}

		if(flag) printf("YES\n");
		else printf("NO\n");

		delete t;

		--T;
	}


	return 0;
}
