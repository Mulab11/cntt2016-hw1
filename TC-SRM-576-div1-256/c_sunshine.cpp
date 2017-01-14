#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class ArcadeManao
{
	public:
	int n,m;
	vector<string> s;
	int f[55][55];
	int qx[5555],qy[5555],qh,qt;
	bool check(int L,int tx,int ty)//Use Breadth first search to check if Manao can fetch the coin.
	{
		memset(f,0,sizeof(f));
		f[n-1][0]=1;
		qh=0,qt=1;qx[1]=n-1;qy[1]=0;
		while(qh<qt)
		{
			int x,y;
			qh++;x=qx[qh],y=qy[qh];
			if(y-1>=0&&s[x][y-1]=='X'&&!f[x][y-1])//Go left.
			{
				f[x][y-1]=1;
				qt++;qx[qt]=x,qy[qt]=y-1;
			}
			if(y+1<m&&s[x][y+1]=='X'&&!f[x][y+1])//Go right.
			{
				f[x][y+1]=1;
				qt++;qx[qt]=x,qy[qt]=y+1;
			}
			for(int h=max(x-L,0);h<n&&h<=x+L;h++)//Use the ladder to climb up or down.
				if(s[h][y]=='X'&&!f[h][y])
				{
					f[h][y]=1;
					qt++;qx[qt]=h,qy[qt]=y;
				}
		}
		return f[tx][ty];
	}
	
	int shortestLadder(vector<string> level,int coinRow,int coinColumn)
	{
		s=level;
		n=s.size();
		m=s[0].size();
		int low=-1,high=55,mid;
		//Use dichotomy to determine the minimum valid length
		while(low+1<high)
		{
			mid=low+high>>1;
			if(check(mid,coinRow-1,coinColumn-1))high=mid;
			else low=mid;
		}
		return high;
	}
};

