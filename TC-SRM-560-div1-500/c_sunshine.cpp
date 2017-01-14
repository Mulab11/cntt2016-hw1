#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int N=310;
class DrawingPointsDivOne
{
	public:
	int n;
	bool c[2][330][330],b[330][330];
	
	void extend(int p)//Do inverse operations.
	{
		int q=p^1;
		memset(c[q],0,sizeof(c[q]));
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				if(c[p][i][j])
					c[q][i][j]=c[q][i][j+1]=c[q][i+1][j]=c[q][i+1][j+1]=1;
	}
	
	void simulate(int p)//Do operations
	{
		int q=p^1;
		memset(c[q],0,sizeof(c[q]));
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				c[q][i][j]=(c[p][i][j]&&c[p][i][j+1]&&c[p][i+1][j]&&c[p][i+1][j+1]);
	}
	
	bool check(int step)
	{
		memcpy(c[0],b,sizeof(b));
		//We store only the current and the last patterns to save memory.
		for(int i=0;i<step;i++)
			extend(i&1);
		for(int i=step;i>0;i--)
			simulate(i&1);
		//Check if the original pattern fits.
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				if(c[0][i][j]!=b[i][j])return 0;
		return 1;
	}
	
	int maxSteps(vector<int> x,vector<int> y)
	{
		n=x.size();
		for(int i=0;i<n;i++)
		{
			x[i]+=70,y[i]+=70;
			b[x[i]][y[i]]=1;
		}
		int low=0,high=150,mid;
		//Use dichotomy to find the maximum k.
		while(low+1<high)
		{
			mid=low+high>>1;
			if(check(mid))low=mid;
			else high=mid;
		}
		if(high==150)return -1;//Impossible if k > 139.
		else return low;
	}
};

