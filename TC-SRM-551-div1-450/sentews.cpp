#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;
class ColorfulWolves
{
	public:
	int n,m;int dis[55][55]={};
	int getmin(vector<string> colormap)
	{
		n=colormap.size();
		m=colormap[0].size();
		for(int i=0;i<55;i++)
			for(int j=0;j<55;j++)
				dis[i][j]=131313131;
		for(int i=0;i<n;i++)
		{
			int temp=0;
			for(int j=0;j<m;j++)
				if(colormap[i][j]=='Y')
					dis[i][j]=temp++;
		}
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					if(dis[i][j]>dis[i][k]+dis[k][j])
						dis[i][j]=dis[i][k]+dis[k][j];
		if(dis[0][n-1]>22222)dis[0][n-1]=-1;
		return dis[0][n-1];
	}
};
