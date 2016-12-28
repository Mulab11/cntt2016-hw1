#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
bool f[55][55]={};
bool g[55][1111]={};
int v[55]={},n;
struct ff{int x,v;}q[55555]={};int tou=0,wei=0;
class XorTravelingSalesman
{
	public:
	int maxProfit(vector <int> cityValues, vector <string> roads)
	{
		n=cityValues.size();
		for(int i=0;i<n;i++)
			v[i]=cityValues[i];
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(roads[i][j]=='Y')
					f[i][j]=1;
		tou=0,wei=0;
		g[0][v[0]]=1;q[0].x=0,q[0].v=v[0];
		while(tou<=wei)
		{
			int tx=q[tou].x,tv=q[tou].v;
			for(int i=0;i<n;i++)
				if(f[tx][i])
					if(!g[i][tv^v[i]])
						g[i][tv^v[i]]=1,q[++wei].x=i,q[wei].v=tv^v[i];
			tou++;
		}
		for(int i=1023;i>=0;i--)
			for(int j=0;j<n;j++)
				if(g[j][i])
					return i;
		return 0;
	}
};
