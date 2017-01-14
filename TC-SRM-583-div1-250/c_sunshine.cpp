#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class TravelOnMars
{
	public:
	int n;
	int g[55][55],q[55],qh,qt;
	int d[55];
	int minTimes(vector<int> range,int startCity,int endCity)
	{
		n=range.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<=range[i];j++)
				g[i][(i+j)%n]=g[i][(i-j+n*100)%n]=1;
		//Use breadth first serch to determine the shortest path.
		memset(d,-1,sizeof(d));d[startCity]=0;
		q[++qt]=startCity;
		for(int x,y;qh<qt;)
		{
			x=q[++qh];
			for(y=0;y<n;y++)
				if(g[x][y]&&d[y]==-1)
				{
					d[y]=d[x]+1;
					q[++qt]=y;
				}
		}
		return d[endCity];
	}
};


