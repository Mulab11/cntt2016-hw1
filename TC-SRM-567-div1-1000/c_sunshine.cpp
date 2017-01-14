#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
typedef long long LL;
const int M=1000000009;

inline int ABS(const int &a)
{return a<0?-a:a;}

class Mountains
{
	public:
	vector<int> height;
	bool graph[55][55];
	unordered_map<string,int> mem;
	
	int calc(int m,vector<int> h)//It is enough to record the height in each position.
	{
		if(!m)
			return 1;
		int X=h.size(),pos=m-1;
		string tmp;tmp+=pos;
		for(int i=0;i<X;i++)tmp+=" ",tmp+=h[i];
		if(mem.count(tmp))return mem[tmp];//this status has been visited.
		int &res=mem[tmp];
		res=0;
		for(int i=0;i<X;i++)//pick the position of the mountain top.
		{
			bool flag=1;
			for(int j=0;j<X&&flag;j++)
				if((height[pos]-ABS(i-j)>h[j])!=graph[pos][j])flag=0;
			if(flag)
			{
				vector<int> h_(X);//get the heights.
				for(int j=0;j<X;j++)
					h_[j]=max(h[j],height[pos]-ABS(i-j));
				res=(res+calc(pos,h_))%M;
			}
		}
		return res;
	}
	
	int countPlacements(vector<int> heights,vector<string> vis)
	{
		int n=heights.size(),X=vis[0].size();
		height=heights;
		for(int i=0;i<n;i++)
			for(int j=0;j<X;j++)
				if(vis[i][j]=='X')graph[i][j]=1;
		vector<int> h(X);
		//We can prove that each mountain visible has at most two available position.
		//So a memorial depth first search is good.
		return calc(n,h);
	}
};

