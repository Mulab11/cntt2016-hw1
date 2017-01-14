#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int MIN=-36,MAX=36;
class CentaurCompany
{
	public:
	int n;
	vector<int> G[44];
	int siz[44];
	bool fvis[44][80][3],gvis[44][44][80][3];
	double fmem[44][80][3],gmem[44][44][80][3];
	
	void tdfs(vector<int> &a,vector<int> &b,int x,int pa)//add edges.
	{
		siz[x]=1;
		for(int i=0,y;i<a.size();i++)
		{
			y=pa;
			if(a[i]-1==x)y=b[i]-1;
			else if(b[i]-1==x)y=a[i]-1;
			if(y!=pa)
			{
				G[x].push_back(y);
				tdfs(a,b,y,x);
				siz[x]+=siz[y];
			}
		}
	}
	//Number of ways to color x's subtrees,
	//with the edges whose index greater than or equal to e.
	//For color 1: 2*c1-n1=s1
	double g(int x,int e,int s1,int xc)
	{
		if(gvis[x][e][s1-MIN][xc])
			return gmem[x][e][s1-MIN][xc];
		gvis[x][e][s1-MIN][xc]=1;
		double &res=gmem[x][e][s1-MIN][xc];res=0;
		if(e==G[x].size())
			return res=int(s1==0);
		int rem=0;
		for(int i=e+1;i<G[x].size();i++)
			rem+=siz[G[x][i]];
		int y=G[x][e];
		int lw=max(-siz[y],s1-rem),up=min(siz[y],s1+rem);
		double p,q;
		//Pick j for as s1 of y's subtree.
		for(int j=lw;j<=up;j++)
		{
			p=f(y,j,xc);
			q=g(x,e+1,s1-j,xc);
			res+=p*q;
		}
		return res;
	}
	
	double f(int x,int s1,int pc)
	{
		if(fvis[x][s1-MIN][pc])
			return fmem[x][s1-MIN][pc];
		fvis[x][s1-MIN][pc]=1;
		double &res=fmem[x][s1-MIN][pc];res=0;
		if(x==0)
		{
			//When we use color 1,the number of the components must be increased by 1, and s1 drops by 2.
			if(s1>MIN)res+=g(x,0,s1-1,1);//Use color 1.
			res+=g(x,0,s1,2);//Use color 2.
		}
		else if(pc==1)
		{
			//Use color 1, and the number of vertices of color 1 increase by 1, but the number of slots increase by 2.
      //so s1 increases by 1.
			if(s1<MAX)res+=g(x,0,s1+1,1);
			res+=g(x,0,s1,2);
		}
		else
		{
			res+=g(x,0,s1,2);
			if(s1>MIN)res+=g(x,0,s1-1,1);//Similar with the situation when x=0.
		}
		return res;
	}
	
	double getvalue(vector<int> a,vector<int> b)
	{
		//Let c be the number of components and n be the number of empty slots.
		//the cost will be max(0,2c-n-2)
		n=a.size()+1;
		tdfs(a,b,0,-1);
		int t=MAX-MIN+1;
		double sum=0,ans;
		for(int s1=MIN;s1<=MAX;s1++)
		{
			int cost=max(0,s1-2);
			sum+=f(0,s1,0)*cost;
		}
		//For the Expected value is a linear application, we only need to determine the expected cost of one company.
		ans=2.0*sum/(1LL<<n);
		return ans;
	}
};

