#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class ICPCBalloons
{
	public:
	
	vector<int> bl,bs,pl,ps;
	
	int work(vector<int> b,vector<int> p)
	{
		sort(b.begin(),b.end());
		sort(p.begin(),p.end());
		reverse(b.begin(),b.end());
		reverse(p.begin(),p.end());
		int tot=0,sum=0;
		for(int i=0;i<b.size();i++)
			tot+=b[i];
		for(int i=0;i<p.size();i++)
			sum+=p[i];
		if(tot<sum)return 100000;//the ballons are not enough.
		//It is good to match the problems and ballons be decreasing order.
		for(int i=0;i<p.size();i++)
			if(i<b.size())
				sum-=min(p[i],b[i]);
		return sum;
	}
	
	int minRepaintings(vector<int> balloonCount,string balloonSize,vector<int>maxAccepted)
	{
		for(int i=0;i<balloonCount.size();i++)
			if(balloonSize[i]=='L')
				bl.push_back(balloonCount[i]);
			else
				bs.push_back(balloonCount[i]);
		int ans=1<<20;
		int pn=maxAccepted.size();
		//Pick the size of ballons for each problem, O(2^n).
		for(int s=0;s<1<<pn;s++)
		{
			pl.clear();
			ps.clear();
			for(int i=0;i<pn;i++)
				if(s>>i&1)
					pl.push_back(maxAccepted[i]);
				else
					ps.push_back(maxAccepted[i]);
			ans=min(ans,work(bl,pl)+work(bs,ps));
		}
		if(ans<=10000)return ans;
		return -1;
	}
};

