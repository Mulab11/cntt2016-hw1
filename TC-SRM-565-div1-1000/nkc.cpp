#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
struct UnknownTree
{
	map<int,vector<int> >p[3];
	vector<int>X;
	static const int mod=1e9+9;
	int cal(vector<int>A)
	{
		sort(A.begin(),A.end());
		if(A[0]!=0) return 0;
		long long ret=1;
		int i,j,now=0,tmp=1;
		for(i=1;i<A.size();i++)
		{
			if(A[i]==A[i-1])
			{
				ret=ret*now%mod;
				tmp++;
			}
			else
			{
				now+=tmp;tmp=1;
				ret=ret*now%mod;
			}
		}
		return ret;
	}
	int doit(vector<int>B,vector<int>A,vector<int>C,int AB,int AC)
	{
		if(AB<=0||AC<=0) return 0;
		int n=A.size(),i,j,k,x,y,z;
		p[0].clear();p[0][0].push_back(0);
		p[1].clear();p[1][AB].push_back(0);
		p[2].clear();p[2][AC].push_back(0);
		bool he=true;
		for(i=0;i<n;i++)
		{
			x=A[i];
			y=B[i]-AB;
			z=C[i]-AC;
			if(x==y&&y==z) p[0][0].push_back(x);
			else if(x==y)
			{
				if((x-z)&1) he=false;
				p[2][(x-z)/2].push_back((x+z)/2);
			}
			else if(x==z)
			{
				if((x-y)&1) he=false;
				p[1][(x-y)/2].push_back((x+y)/2);
			}
			else he=false;
		}
		if(!he) return 0;
		long long tmp=1;
		for(k=1;k<3;k++)
		{
			map<int,vector<int> >::iterator it;
			for(it=p[k].begin();it!=p[k].end();it++)
			(tmp*=cal(it->second))%=mod;
		}
		(tmp*=cal(p[0][0]))%=mod;
		return tmp;
	}
	int solve(vector<int>B,vector<int>A,vector<int>C)
	{
		int i,j;
		long long ret=0;
		int ll=min_element(A.begin(),A.end())-A.begin();
	//	swap(A[0],A[ll]);swap(B[0],B[ll]);swap(C[0],C[ll]);
		ret+=doit(B,A,C,B[ll]-A[ll],A[ll]+C[ll]);
		ret+=doit(B,A,C,B[ll]+A[ll],C[ll]-A[ll]);
		ret+=doit(B,A,C,B[ll]-A[ll],C[ll]-A[ll]);
		ret+=doit(B,A,C,A[ll]-B[ll],C[ll]-A[ll]);
		ret+=doit(B,A,C,B[ll]-A[ll],A[ll]-C[ll]);
		return ret%mod;
	}
	int getCount(vector <int> distancesA, vector <int> distancesB, vector <int> distancesC)
	{
		int n=distancesA.size();
		int A,B,C;
		int i,j,k,l,x,y,z,u,v;
		int ans=0;
		for(i=0;i<n;i++)
		{
			A=distancesA[i];
			B=distancesB[i];
			C=distancesC[i];
			p[0].clear();p[0][A].push_back(0);
			p[1].clear();p[1][B].push_back(0);
			p[2].clear();p[2][C].push_back(0);
			X.clear();X.push_back(0);
			bool he=true;
			for(j=0;j<n;j++)
			if(i!=j)
			{
				x=distancesA[j]-A;
				y=distancesB[j]-B;
				z=distancesC[j]-C;
				if(x==y&&y==z&&x>0) X.push_back(x);
				else if(x==y&&x>0)
				{
					if((x-z)&1) he=false;
					p[2][(x-z)/2].push_back((x+z)/2);
				}
				else if(x==z&&x>0)
				{
					if((x-y)&1) he=false;
					p[1][(x-y)/2].push_back((x+y)/2);
				}
				else if(y==z&&y>0)
				{
					if((y-x)&1) he=false;
					p[0][(y-x)/2].push_back((x+y)/2);
				}
				else he=false;
			}
			if(!he) continue;
			long long tmp=1;
			for(k=0;k<3;k++)
			{
				map<int,vector<int> >::iterator it;
				for(it=p[k].begin();it!=p[k].end();it++)
				(tmp*=cal(it->second))%=mod;
			}
			(tmp*=cal(X))%=mod;
			(ans+=tmp)%=mod;
		}
		(ans+=solve(distancesA,distancesB,distancesC))%=mod;
		(ans+=solve(distancesB,distancesA,distancesC))%=mod;
		(ans+=solve(distancesA,distancesC,distancesB))%=mod;
		return ans;
	}
};