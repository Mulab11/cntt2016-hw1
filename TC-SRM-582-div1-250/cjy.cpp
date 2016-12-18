#include<bits/stdc++.h>
using namespace std;
vector<pair<int,long long> >e;
int n,m,i,j;
long long S,ans;
class SpaceWarDiv1
{
	public:
		long long minimalFatigue(vector<int> g,vector<int> s,vector<long long> c)
		{
			for(n=g.size(),m=s.size();i<m;i++)e.push_back(make_pair(s[i],c[i]));
			sort(e.begin(),e.end());
			sort(g.begin(),g.end());
			for(i=m-1,j=n-1;~i;i--)//贪心
			{
				S+=e[i].second;
				while(~j&&g[j]>=e[i].first)j--;
				if(j==n-1)return -1;
				ans=max(ans,(S+n-2-j)/(n-1-j));
			}
			return ans;
		}
};
