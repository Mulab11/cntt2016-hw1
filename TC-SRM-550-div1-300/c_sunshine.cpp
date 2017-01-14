#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
class RotatingBot
{
	public:
	vector<pair<int,int> > p1,p2;
	bool s[666][666],t[666][666];
	int xl,xr,yl,yr;
	int minArea(vector<int> moves)
	{
		int x,y;
		x=300,y=300;
		xl=xr=yl=yr=300;
		s[x][y]=1;
		int d=0;
		for(int i=0;i<moves.size();i++)//Find the minimum circumscribed rectangle.
		{
			for(int j=0;j<moves[i];j++)
			{
				x=x+dx[d];
				y=y+dy[d];
				if(s[x][y])return -1;
				s[x][y]=1;
				xl=min(xl,x);
				xr=max(xr,x);
				yl=min(yl,y);
				yr=max(yr,y);
				p1.push_back(make_pair(x,y));
			}
			d=d+1&3;
		}
		for(int i=0;i<600;i++)
			for(int j=0;j<600;j++)
				if(i<xl||i>xr||j<yl||j>yr)
					t[i][j]=1;//mark the inavailable cells. 
		x=y=300;d=0;
		t[x][y]=1;
		int cnt=0;
		for(int i=0;i<moves.size();i++)
			cnt+=moves[i];
		for(int i=1;i<=cnt;i++)//Run the robot's program.
		{
			if(t[x+dx[d]][y+dy[d]])d=d+1&3;
			if(t[x+dx[d]][y+dy[d]])return -1;
			x+=dx[d];
			y+=dy[d];
			t[x][y]=1;
			p2.push_back(make_pair(x,y));
		}
		if(p1!=p2)return -1;//Check the path.
		return (xr-xl+1)*(yr-yl+1);
	}
	
};

