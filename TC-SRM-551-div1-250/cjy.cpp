#include<bits/stdc++.h>
using namespace std;
int i,j,k,s,t,p,q,r,n;
class ColorfulChocolates
{
	public:
		int maximumSpread(string c,int m)
		{
			for(n=c.size();i<n;i++)for(s=0,j=p=i;~j&&s<=m;j--)
			{
				if(c[i]==c[j])s+=p-j,p--;
				for(t=s,k=q=i;k<n&&t<=m;k++)if(c[i]==c[k])if(t+=k-q,q++,t<=m)r=max(r,q-p-1);
			}
			return r;
		}
};
