#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class XorTravelingSalesman
{
	public:
	bool f[55][1024];
	queue<pair<int,int> > Q;
	int maxProfit(vector<int> cityValues,vector<string> roads)
	{
		//f[i][j] represents the state that we are in city i and the current value is j.
		f[0][cityValues[0]]=1;
		Q.push(make_pair(0,cityValues[0]));
		while(!Q.empty())//We can simply use breadth first search to get all available states.
		{
			int x,c;
			x=Q.front().first;
			c=Q.front().second;
			Q.pop();
			for(int i=0;i<cityValues.size();i++)//Pick the next city to go.
				if(roads[x][i]=='Y'&&!f[i][c^cityValues[i]])
				{
					f[i][c^cityValues[i]]=1;
					Q.push(make_pair(i,c^cityValues[i]));
				}
		}
		for(int k=1023;~k;k--)//Find the maximum available value.
			for(int i=0;i<cityValues.size();i++)
				if(f[i][k])return k;
	}
};

