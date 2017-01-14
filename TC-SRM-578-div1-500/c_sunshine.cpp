#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;
const int M=1000000007;
class WolfInZooDivOne
{
	public:
	int N;
	vector<int> lt,rt;
	vector<pair<int,int> > range;
	
	int f[333][333],cur[333];
	
	vector<int> get_in(string str)
	{
		stringstream tmp;int t;
		vector<int> res;
		tmp<<str;
		while(tmp>>t)res.push_back(t);
		return res;
	}
	int count(int N,vector<string> L,vector<string> R)
	{
		this->N=N;
		string in_L,in_R;
		for(int i=0;i<L.size();i++)in_L+=L[i];
		for(int i=0;i<R.size();i++)in_R+=R[i];
		lt=get_in(in_L);
		rt=get_in(in_R);
		for(int i=0;i<lt.size();i++)
			range.push_back(make_pair(lt[i]+1,rt[i]+1));
		sort(range.begin(),range.end());
		vector<pair<int,int> > range_;
		//If interval A completely contains interval B, we can delete B.
		for(int i=0,rr=-1;i<range.size();i++)
			if(range[i].second>rr)
				range_.push_back(range[i]),rr=range[i].second;
		range=range_;
		//cur[i] : the last range satisfying left end is less than or equal to i.
		for(int i=0,j=0;i<=N;i++)
		{
			for(;j<range.size()&&range[j].first<=i;j++);
			cur[i]=j-1;
		}
		//f[i][j] (i<j): Ways to place wolves in interval [1,j] that the last two wolves are at section i and j.
		f[0][0]=1;
		int t;
		for(int j=0;j<=N;j++)
			for(int i=0;i<=j;i++)
				if((t=f[i][j])!=0)
					for(int k=j+1;k<=N;k++)//find a place to place the next wolf.
						if(cur[i]==-1||range[cur[i]].second<k)
							(f[j][k]+=t)%=M;
		int ans=0;
		//Pick all possible positions and count the answer.
		for(int i=0;i<=N;i++)//i=0 means there is only one wolf.
			for(int j=i;j<=N;j++)
			{
				ans+=f[i][j];
				ans%=M;
			}
		return ans;
	}
};

