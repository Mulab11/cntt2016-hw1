#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int M=1000000009;

inline void up(int &x,const int &y)
{x=(x+y)%M;}

class StringPath
{
	public:
	int f[8][8][1<<8][1<<8];
	int countBoards(int n,int m,string A,string B)
	{
		//Because we can only go down and right, cell (i,j) must match A[i+j] if string A go though it.
		//The only cells we need to know if string A/B can go through them are the last m cells,
		//if we fill in cells from top to bottom and from left to right in each row.
		//f[i][j][sa][sb]: We have filled out all cells (x<i or x=i and y<=j),
		//and the status that last m cells fit string A can be represented by sa. Sb is similar.
		
		//fill in the first cell (0,0) 
		if(A[0]==B[0])
			f[0][0][1][1]=1,f[0][0][0][0]=25;
		else
			f[0][0][0][1]=f[0][0][1][0]=1,f[0][0][0][0]=24;
		int t,ta,tb,ua,ub;
		for(int i=0;i<n;i++)
			for(int j=0;j<m-(i==n-1);j++)
				for(int sa=0;sa<1<<m;sa++)
					for(int sb=0;sb<1<<m;sb++)
						if(t=f[i][j][sa][sb])
						{
							int x=i,y=j+1;
							if(y==m)y=0,x++;
							//A cell can be reached if one of the cells on its upper and left side fits the string
							ta=sa|(sa<<1&1<<y);
							tb=sb|(sb<<1&1<<y);
							//ta/tb: The new status, if the current cell match the string A/B
							ua=ta&~(1<<y);
							ub=tb&~(1<<y);
							//ua/ub: The new status, if the current cell do not match the string A/B
							if(A[x+y]==B[x+y])
							{
								up(f[x][y][ta][tb],t);
								up(f[x][y][ua][ub],25LL*t%M);
							}
							else
							{
								up(f[x][y][ta][ub],t);
								up(f[x][y][ua][tb],t);
								up(f[x][y][ua][ub],24LL*t%M);
							}
						}
		int ans=0;
		//Count the ways. Notice that the last cell must can be reached by both A and B.
		for(int sa=1<<m-1;sa<1<<m;sa++)
			for(int sb=1<<m-1;sb<1<<m;sb++)
				up(ans,f[n-1][m-1][sa][sb]);
		return ans;
	}
};

