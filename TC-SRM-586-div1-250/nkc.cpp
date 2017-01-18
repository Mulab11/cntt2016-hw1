#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct PiecewiseLinearFunction
{
	int maximumSolutions(vector <int> Y)
	{
		int i,j,x,n=Y.size();
		int ans=0;
		for(i=1;i<n;i++)
		if(Y[i-1]==Y[i]) return -1;
		for(i=0;i<n;i++)
		{
			x=Y[i];
			int now=0;
			//计算整点下方直线与图像交点 
			for(j=1;j<Y.size();j++)
			if((Y[j-1]<x&&Y[j]>=x)||(Y[j-1]>=x&&Y[j]<x)) now++;
			ans=max(ans,now);now=0;
			//计算整点上方直线与图像交点 
			for(j=1;j<Y.size();j++)
			if((Y[j-1]<=x&&Y[j]>x)||(Y[j-1]>x&&Y[j]<=x)) now++;
			ans=max(ans,now);now=0;
			//计算整点所在直线与图像交点 
			for(j=1;j<Y.size();j++)
			if((Y[j-1]<=x&&Y[j]>x)||(Y[j-1]>=x&&Y[j]<x)) now++;
			if(Y[Y.size()-1]==x) now++;
			ans=max(ans,now);
		}
		return ans;
	}
};