#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

inline double sqr(const double &x)
{return x*x;}

class CandyOnDisk
{
	public:
	int n;
	double d[55][55];
	double l[55],h[55];
	bool used[55][55],vis[55],upd;
	
	bool cross(double l1,double r1,double l2,double r2)
	{
		if(l1>r2||l2>r1)return 0;
		return 1;
	}
	
	string ableToAchieve(vector<int> x,vector<int> y,vector<int> r,int sx,int sy,int tx,int ty)
	{
		if(sx==tx&&sy==ty)return "YES";
		//Delete the extra disks whose centres coincide.
		for(int i=0;i<x.size();i++)
			for(int j=i+1;j<x.size();j++)
				if(x[i]==x[j]&&y[i]==y[j])
				{
					r[i]=max(r[i],r[j]);
					x[j]=x[x.size()-1];x.pop_back();
					y[j]=y[x.size()-1];y.pop_back();
					r[j]=r[x.size()-1];r.pop_back();
				}
		n=x.size();
		//d[i][j]: the dist between i-th disk's and j-th disk's centres.
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				d[i][j]=sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
		for(int i=0;i<n;i++)
		{
			double ds=sqrt(sqr(x[i]-sx)+sqr(y[i]-sy));
			if(ds<r[i])l[i]=h[i]=ds,vis[i]=1;
			else l[i]=1e9,h[i]=-1e9;
		}
		//The area of each disk that can be reached is a annulus.
		//We only need to record the minimum radio l[i] and maximum radio h[i].
		upd=1;
		//Use the algorithm analogous to Bellman-Ford to update the available area.
		while(upd)
		{
			upd=0;
			for(int i=0;i<n;i++)
				if(vis[i])
					for(int j=0;j<n;j++)
						if(!used[i][j]&&j!=i)
						{
							double lj=max(0.,d[i][j]-r[j]),hj=d[i][j]+r[j];
							if(!used[i][j]&&cross(l[i],h[i],lj,hj))//disk i can update disk j.
							{
								//We use i to update the radio range of j at most once.
								used[i][j]=vis[j]=upd=1;
								//update j-th disk's range.
								l[i]=min(l[i],lj);
								h[i]=max(h[i],min(double(r[i]),hj));
								l[j]=min(l[j],max(d[i][j]-r[i],0.));
								h[j]=max(h[j],min(d[i][j]+r[i],double(r[j])));
							}
						}
		}
		for(int i=0;i<n;i++)
		{
			double dt=sqrt(sqr(x[i]-tx)+sqr(y[i]-ty));
			if(l[i]<dt&&dt<h[i])return "YES";
		}
		return "NO";
	}
};

