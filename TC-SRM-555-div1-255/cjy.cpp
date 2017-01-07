#include<bits/stdc++.h>
using namespace std;
long long x,t;
int n,f[51],i,j;
class CuttingBitString//DP
{
	public:
		int getmin(string s)
		{
			for(n=s.size(),i=n-1;~i;i--)for(x=0,f[i]=99,j=i;j<n;j++)
			{
				if(x=x*2+s[j]-48,!x)break;
				for(t=x;t%5==0;t/=5);
				if(t==1)f[i]=min(f[i],f[j+1]+1);
			}
			return f[0]<99?f[0]:-1;
		}
};
