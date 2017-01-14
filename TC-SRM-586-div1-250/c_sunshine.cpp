#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class PiecewiseLinearFunction
{
	public:
	vector<int> Y;
	
	int cnti(int y)//count roots if y is a integer
	{
		int res=0;
		for(int i=0;i<Y.size();i++)
			if(Y[i]==y)res++;
		for(int i=0;i+1<Y.size();i++)
			if((Y[i]<y&&Y[i+1]>y)||(Y[i]>y&&Y[i+1]<y))
				res++;
		return res;
	}
	
	int cnt(double y)//count roots if y+.5 is a integer
	{
		int res=0;
		for(int i=0;i+1<Y.size();i++)
			if((Y[i]<y&&Y[i+1]>y)||(Y[i]>y&&Y[i+1]<y))
				res++;
		return res;
	}
	
	int maximumSolutions(vector<int> Y)
	{
		for(int i=0;i+1<Y.size();i++)
			if(Y[i]==Y[i+1])return -1;
		this->Y=Y;
		int ans=0;
		for(int i=0;i<Y.size();i++)//We can always set y=Y[i],Y[i]-.5,Y[i]+.5 to get the maximum roots  
			ans=max(max(ans,cnti(Y[i])),max(cnt((double)Y[i]-0.5),cnt((double)Y[i]+0.5)));
		return ans;
	}
};

