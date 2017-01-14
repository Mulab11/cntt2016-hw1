#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;

class AlternateColors2
{
	public:
	LL f[100005][8][3];
	int col[3];
	LL countWays(int n,int k)
	{
		//Use DP to solve it and f[i][j][k] means we have destroyed i balls and the remaining colors' mask is j and the color cycle starts at k.
		for(int i=n;~i;i--)
		{
			for(int mask=1;mask<8;mask++)
			{
				int t=0;
				for(int j=0;j<3;j++)
					if((mask&1<<j)!=0)col[t++]=j;
				for(int p=0;p<t;p++)
				{
					LL &res=f[i][mask][p];
					res=0;
					if(i==n)res=1;
					else
					{
						//Place the color
						//Do not count the case in which a non-red ball is placed in position k.
						if(k-1!=i||col[p]==0)res+=f[i+1][mask][(p+1)%t];
						//Do not place the p-th color. Not ever again.
						if(t>1)
						{
							int nmask=mask^1<<col[p];
							res+=f[i][nmask][p%(t-1)];
						}
					}
				}
			}
		}
		return f[0][7][0];
	}
};

