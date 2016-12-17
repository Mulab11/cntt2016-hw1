#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
bool vis[1111][1111]={};
int xx=500,yy=500;
int minx=500,miny=500,maxx=500,maxy=500;
class RotatingBot
{
	public:
	int minArea(vector<int> moves)
	{
		int n=moves.size();
		for(int i=0;i<=1000;i++)
			for(int j=0;j<=1000;j++)
				vis[i][j]=1;
		for(int i=0;i<n;i++)
		{
			xx+=dx[i&3]*moves[i],yy+=dy[i&3]*moves[i];
			if(xx<minx)minx=xx;
			if(yy<miny)miny=yy;
			if(xx>maxx)maxx=xx;
			if(yy>maxy)maxy=yy;
		}
		for(int i=minx;i<=maxx;i++)
			for(int j=miny;j<=maxy;j++)
				vis[i][j]=0;
		xx=yy=500;
		vis[500][500]=1;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<moves[i];j++)
			{
				xx+=dx[i&3],yy+=dy[i&3];
				if(vis[xx][yy]||xx>maxx||xx<minx||yy>maxy||yy<miny)return -1;//重复或超出边界无解
        vis[xx][yy]=1;
			}
			if(!vis[xx+dx[i&3]][yy+dy[i&3]]&&i!=n-1)//不该转向的时候转向，无解
return -1;
		}
		return (maxx-minx+1)*(maxy-miny+1);
	}
};
