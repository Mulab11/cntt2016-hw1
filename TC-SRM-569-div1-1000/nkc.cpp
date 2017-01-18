#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct RobotHerb
{
	long long getdist(int T, vector <int> a)
	{
		long long x=0,y=0,now=0;
		int i,j;
		for(i=0;i<a.size();i++)
		{
			if(now==0) y+=a[i];
			if(now==1) x+=a[i];
			if(now==2) y-=a[i];
			if(now==3) x-=a[i];
			(now+=a[i])%=4;
		}
		if(now==0) return (abs(x)+abs(y))*T;//方向相同直接计算 
		T%=4;//方向不同四次一定循环 
		long long xx=0,yy=0,nnow=0;
		for(i=1;i<=T;i++)
		{
			if(nnow==0) xx+=x,yy+=y;
			if(nnow==1) yy-=x,xx+=y;
			if(nnow==2) xx-=x,yy-=y;
			if(nnow==3) xx-=y,yy+=x;
			(nnow+=now)%=4;
		}
		return abs(xx)+abs(yy);
	}
};