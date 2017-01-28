#include <cstdio>
#define NMAX 11111
int input[NMAX];
int N;

using namespace std;

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		bool flag=true;
		scanf("%d",&N);
		for(int i=0;i<N;++i) scanf("%d",&input[i]);

		for(int i=0;i<N-1;++i){
			input[i+1]-=input[i];
			if(input[i+1]<0){
				flag=false;
				break;
			}
		}

		if(input[N-1]!=0 || flag==false) printf("NO\n");
		else printf("YES\n");
	}


	return 0;
}

