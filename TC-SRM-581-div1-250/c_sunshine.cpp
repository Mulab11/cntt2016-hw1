#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class SurveillanceSystem
{
	public:
	int n,L;
	string s;
	vector<int> ph;
	int cov[55],noc[55];
	int work(int pos,int flag)
	{
		int cnt=0;
		for(int i=0;i<L;i++)
			cnt+=(s[i]=='X');
		memset(cov,0,sizeof(cov));
		memset(noc,0,sizeof(noc));
		//cov/noc[k] : the number of intervals that monitor k containers and do/don't monitor pos-th sector.
		for(int i=0,j=L;j<=s.size();i++,j++)
		{
			if(pos>=i&&pos<j)
				cov[cnt]++;
			else
				noc[cnt]++;
			cnt-=(s[i]=='X');
			if(j<s.size())
				cnt+=(s[j]=='X');
		}
		if(flag==0)
		{
			for(int i=0;i<ph.size();i++)
				if(--noc[ph[i]]<0)return 0;//must be monitored
			return 1;
		}
		else
		{
			for(int i=0;i<ph.size();i++)
				if(cov[ph[i]])return 1;//mustn't be monitored
			return 0;
		}
	}
	
	string getContainerInfo(string containers,vector<int> reports,int L)
	{
		n=containers.size();this->L=L;
		s=containers;ph=reports;
		string res;
		//Try each sector and check if it can be monitored or not monitored
		for(int i=0;i<containers.size();i++)
		{
			int f0=work(i,0);//must not monitored
			int f1=work(i,1);//must monitored
			if(f0&&f1)res+='?';
			else if(f0)res+='-';
			else res+='+';
		}
		return res;
	}
};

