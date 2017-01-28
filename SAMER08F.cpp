//============================================================================
// Name        : SAMER08F.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#define NMAX 101
using namespace std;

typedef long long int LL;

LL res[NMAX];

void init(){
	res[0]=0;
	for(int i=1;i<NMAX;++i) res[i]=res[i-1]+((LL)i*i);
}

int main() {

	init();
	while(1){
		int N;
		cin>>N;

		if(N==0) break;

		cout<<"\n"<<res[N];
	}



	return 0;
}
