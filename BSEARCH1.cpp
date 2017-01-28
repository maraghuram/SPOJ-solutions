#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> input;

int binary_search(int x,int i,int j){
	if(i>j) return -1;
	int mid=(i+j)>>1;

	if(input[mid]>x) return binary_search(x,i,mid-1);
	else if(input[mid]<x) return binary_search(x,mid+1,j);
	else return mid;
}

int binary_search_helper(int x,int i,int j){
	int pos=binary_search(x,i,j);
	if(pos==-1) return -1;
	while(pos>0 && input[pos]==input[pos-1]) --pos;
	return pos;
}


int main()
{
	int N,Q;
	scanf("%d %d",&N,&Q);
	input=vector<int>(N);

	for(int i=0;i<N;++i) scanf("%d",&input[i]);
	for(int i=0;i<Q;++i){
		int x,pos;
		scanf("%d",&x);
		pos=binary_search_helper(x,0,N-1);
		printf("%d\n",pos);
	}

	return 0;
}
