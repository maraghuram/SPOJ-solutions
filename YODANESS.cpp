#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef long long int x64;

const int MAX=30000;

vector<int> tree,input;

x64 read(int idx)
{
	x64 res=0;

	while(idx>0)
	{
		res+=tree[idx];
		idx-=( idx & -idx);
	}

	return res;
}

void update(int idx)
{
	while(idx<=tree.size()-1)
	{
		tree[idx]+=1;
		idx+=( idx & -idx);
	}
}

x64 countInversions(int N)
{
	x64 inv_count=0;
	tree.clear();
	tree.resize(N+1,0);

	for(int i=N-1;i>=0;--i)
	{
		inv_count+=read(input[i]-1);
		update(input[i]);
	}

	return inv_count;
}

int main()
{
	int T;
	vector<string> sentence;
	map<string,int> code=map<string,int>();

	scanf("%d",&T);

	while(T>0)
	{
		int N;
		char word[21];
		scanf("%d",&N);
		sentence.resize(N,"");
		input.resize(N,0);
		code.clear();

		for(int i=0;i<N;++i)
		{
			scanf("%s",word);
			sentence[i]=string(word);
		}

		for(int i=0;i<N;++i)
		{
			scanf("%s",word);
			code[string(word)]=i+1;
		}

		for(int i=0;i<N;++i)
			input[i]=code[string(sentence[i])];

		printf("%lld\n",countInversions(N));

		--T;
	}

	return 0;
}
