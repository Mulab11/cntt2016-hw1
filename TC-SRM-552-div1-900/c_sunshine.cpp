#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn=1000005;

class HolyNumbers
{
	public:
	vector<int> p;
	bool isp[maxn];
	
	void init(int N)//Get prime numbers
	{
		for(int i=2;i<=N;i++)
		{
			if(!isp[i])p.push_back(i);
			for(int j=0;j<p.size()&&i*p[j]<=N;j++)
			{
				isp[i*p[j]]=1;
				if(i%p[j]==0)break;
			}
		}
	}
	
	LL dfs(int x,LL m)
	{
		if(x==p.size()||p[x]>m)return 1;//Find one valid number.
		//For unique factorization theorem, we never count a number twice.
		if((LL)p[x]*p[x]>m)//We can multiply the number by at most one prime number.
			return upper_bound(p.begin()+x,p.end(),m)-p.begin()-x+1;//Find the number of all valid prime numbers.
		LL res=dfs(x+1,m);
		for(LL p2=(LL)p[x]*p[x],pk=p[x];pk<=m;pk*=p2)//pick the power exponent of the current prime number.
			res+=dfs(x+1,m/pk);
		return res;
	}
	
	LL count(LL upTo,int maximalPrime)
	{
		init(maximalPrime);
		//To be honest, I am not able to prove the time complexity.
		//But it always finishes in the time limit.
		return dfs(0,upTo);
	}
};

