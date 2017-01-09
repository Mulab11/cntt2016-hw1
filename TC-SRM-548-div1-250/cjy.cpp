#include<bits/stdc++.h>
using namespace std;
int l,r=1e9,m,f,h[55],i;
class KingdomAndTrees
{
	public:
		int minLevel(vector<int> a)
		{
			for(;l<r;f?r=m:l=m+1)for(m=l+r>>1,f=i=1;i<=a.size();i++)h[i]=max(h[i-1]+1,a[i-1]-m),f&=abs(h[i]-a[i-1])<=m;
			return l;
		}
};
