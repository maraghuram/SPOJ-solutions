#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	bool flag=true;
	int x,i;
	vector<int> array=vector<int>(0,0);

	i=0;

	while(1==scanf("%d",&x))
	{

		if(x==42)
			flag=false;

		if(flag)
		{
			array.push_back(x);
			++i;
		}

	}

	for(int j=0;j<i;++j)
		printf("%d\n",array[j]);

	return 0;
}
