#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class ShoutterDiv1
{
	public:
	
	int n,ans;
	
	int work(vector<pair<int,int> > bunny)
	{
		n=bunny.size();
		sort(bunny.begin(),bunny.end());
		int mt=bunny[0].second;
		for(int i=1;i<n;i++)
			mt=min(mt,bunny[i].second);
		//Pick all rabbits whose informatiom need to be shared.
		for(int p,i=0,j,k;i<n;i++)
		{
			p=mt;
			for(j=0;j<n;)
			{
				if(bunny[i].first<=p)//We can use itself for free.
					p=max(p,bunny[i].second);
				k=-1;
				//Find the right-most available rabbit to spread the information.
				for(;j<n&&bunny[j].first<=p;j++)
					if(k==-1||bunny[j].second>bunny[k].second)
						k=j;
				if(k==-1)return -1;//Can't reach the right-most rabbit.
				if(j<n)
				{
					ans++;
					p=bunny[k].second;
				}
			}
		}
		return ans;
	}
	
	int count(vector<string> s1000,vector<string> s100,vector<string> s10,vector<string> s1,vector<string> t1000,vector<string> t100,vector<string> t10,vector<string> t1)
	{
		string S1000,S100,S10,S1,T1000,T100,T10,T1;
		for(int i=0;i<s1000.size();i++)S1000+=s1000[i];
		for(int i=0;i<s100.size();i++)S100+=s100[i];
		for(int i=0;i<s10.size();i++)S10+=s10[i];
		for(int i=0;i<s1.size();i++)S1+=s1[i];
		for(int i=0;i<t1000.size();i++)T1000+=t1000[i];
		for(int i=0;i<t100.size();i++)T100+=t100[i];
		for(int i=0;i<t10.size();i++)T10+=t10[i];
		for(int i=0;i<t1.size();i++)T1+=t1[i];
		vector<pair<int,int> > bunny;
		for(int i=0;i<S1.size();i++)
			bunny.push_back(make_pair(
			S1000[i]*1000+S100[i]*100+S10[i]*10+S1[i]*1-53328,
			T1000[i]*1000+T100[i]*100+T10[i]*10+T1[i]*1-53328
			));
		//Above is getting the input.
		return work(bunny);
	}
};

