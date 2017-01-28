#include <cstdio>
#define next(x)	x & -x

const int MAX=1024;

int tree[MAX+1][MAX+1],input[MAX+1][MAX+1];

void reset()
{
	for(int i=0;i<MAX+1;++i)
	{
		for(int j=0;j<MAX+1;++j)
		{
			tree[i][j]=input[i][j]=0;
		}
	}
}

int query(int xIdx,int yIdx)
{
	int result=0;

	while(xIdx>0)
	{
		int y=yIdx;

		while(y>0)
		{
			result+=tree[xIdx][y];
			y-=next(y);
		}

		xIdx-=next(xIdx);
	}

	return result;
}

void update(int xIdx,int yIdx,int set)
{
	int val=set-input[xIdx][yIdx];
	int x=xIdx;

	while(x<=MAX)
	{
		int y=yIdx;
		while(y<=MAX)
		{
			tree[x][y]+=val;
			y+=next(y);
		}

		x+=next(x);
	}

	input[xIdx][yIdx]=set;
}


int main()
{
	int T;

	scanf("%d",&T);

	while(T>0)
	{
		reset();

		int N;

		scanf("%d",&N);

		while(true)
		{
			char str[4];
			scanf("%s",str);

			if(str[0]=='E')
				break;

			else
			{

				if(str[1]=='E')
				{
					int x,y,num;

					scanf("%d %d %d",&x,&y,&num);
					++x;++y;
					update(x,y,num);
				}
				else
				{
					int x1,y1,x2,y2;
					scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
					++x1;++x2;++y1;++y2;
					printf("%d\n",query(x1-1,y1-1)+query(x2,y2)-query(x1-1,y2)-query(x2,y1-1));
				}
			}


		}

		--T;
	}
}
