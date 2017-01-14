#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class StringWeight
{
	public:
	vector<int> L;
	int f[55][28][28];
	
	int dp(int i,int a,int o)//step i, a letters have not occured, o open letter intervals
	{
		int &res=f[i][a][o];
		if(~res)return res;
		res=10000000;
		if(i==L.size())return o==0?res=0:res;
		int s=0;
		for(int j=0;j<i;j++)
			s+=L[j];
		int m=min(L[i],26);//the number of disparate letters 
		for(int c=0;c<=o&&c<=m;c++)//letter intervals that end at B[i]
			for(int p=0;p<=a&&c+p<=m;p++)//letter intervals that start at B[i]
				for(int u=0;c+u<=o&&c+p+u<=m;u++)//letter intervals that strictly include B[i]
				{
					int k=m-c-p-u;//letters intervals that start and end at B[i]
					if(p+k>a)continue;
					int w=dp(i+1,a-p-k,o-c+p);
					if(u)
					{
						//c letters on the left
						//p letters on the right
						//k single letters
						w+=(c-p)*s-(L[i]-1)*p+c*(c-1)/2+p*(p-1)/2;//cost = \sum R - \sum L
					}
					else
					{
						//c letters on the left
						//p letters on the right
						w+=(c-p)*s-(L[i]-1)*p+c*(c-1)/2+p*(p-1)/2;//cost = \sum R - \sum L
						w+=L[i]-c-p-k;//repeated letters cost 1 each
					}
					res=min(res,w);
				}
		return res;
	}
	
	int getMinimum(vector<int> L)
	{
		this->L=L;
		memset(f,-1,sizeof(f));
		return dp(0,26,0);
	}
};

