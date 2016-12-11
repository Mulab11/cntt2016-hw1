#include<bits/stdc++.h>
#define ll long long
using namespace std;
int i,j,k,r,n;
ll ans=1,s;
class XorCards
{
	public:
		ll numberOfWays(vector<ll>a,ll m)
		{
			n=a.size();
			for(i=49;~i;i--)
			{
				r=-1;
				for(j=k;j<n;j++)if(a[j]>>i&1)r=j;
				if(r<0)continue;
				swap(a[k],a[r]);
				for(j=0;j<n;j++)if(j!=k&&(a[j]>>i&1))a[j]^=a[k];
				k++;
			}
			for(i=0;i<n;i++)if((s^a[i])<=m)s^=a[i],ans+=1ll<<n-i-1;
			return ans;
		}
};
