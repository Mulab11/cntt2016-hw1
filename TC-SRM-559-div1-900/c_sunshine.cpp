#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
const double pi=acosl(-1.0),dpi=pi*2;
class CircusTents
{
	public:
	int n;
	vector<int> x,y,r;
	
	double alpha[55],dis[55];
	
	inline double sqr(const double &x){return x*x;}
	
	inline double Mod(double x)
	{
		while(x<0)x+=dpi;
		while(x>dpi)x-=dpi;
		return x;
	}
	
	double dist(double r1,double r2,double x,double theta)
	{
		//There are circle (0,0,r1),(x,0,r2).
		//This function determines the shortest path from the second circle to (r1,theta) in polar coordinates.
		double beta=acos(r1/x);
		theta=Mod(theta);
		if(theta>pi)theta=dpi-theta;
		if(theta<beta)
			return sqrt(sqr(x-r1*cos(theta))+sqr(r1*sin(theta)))-r2;
		return x*sin(beta)+(theta-beta)*r1-r2;
	}
	
	vector<pair<double,int> > E;
	
	void addrange(double l,double r)//split the range into two ranges if it covers 0.
	{
		l=Mod(l),r=Mod(r);
		E.push_back(make_pair(l,-1));
		E.push_back(make_pair(r,1));
		if(l>r)
		{
			E.push_back(make_pair(dpi,1));
			E.push_back(make_pair(0,-1));
		}
	} 
	
	bool check(double length)
	{
		E.clear();
		for(int i=1;i<=n;i++)
		{
			if(dist(r[0],r[i],dis[i],pi)<length)return 1;//All points on circle 0 are invalid.
			if(dist(r[0],r[i],dis[i],0.)>length)continue;//Too far to consider.
			double low=0,high=pi,mid;
			//Use dichotomy to get the angle.
			while(low+1e-12<high)
			{
				mid=(low+high)*.5;
				if(dist(r[0],r[i],dis[i],mid)<length)low=mid;
				else high=mid;
			}
			addrange(alpha[i]-high,alpha[i]+high);//Insert the angle interval.
		}
		sort(E.begin(),E.end());
		if(E.empty()||E.front().first>1e-12||E.back().first<dpi-1e-12)return 0;
		int t=0;
		//Check if the union set is the whole circle.
		for(int i=0;i+1<E.size();i++)
		{
			t+=E[i].second;
			if(t>=0)return 0;
		}
		return 1;
	}
	
	double findMaximumDistance(vector<int> x,vector<int> y,vector<int> r)
	{
		n=r.size()-1;
		this->x=x;
		this->y=y;
		this->r=r;
		for(int i=1;i<=n;i++)
		{
			x[i]-=x[0];y[i]-=y[0];
			dis[i]=sqrt(sqr(x[i])+sqr(y[i]));
			alpha[i]=atan2(y[i],x[i]);
		}
		x[0]=y[0]=0;
		double low=0,high=1e6,mid;
		//Use dichotomy to find the answer.
		for(int TM=100;TM--&&low+1e-10<high;)
		{
			mid=(low+high)*.5;
			if(check(mid))high=mid;
			else low=mid;
		}
		return low;
	} 
};

