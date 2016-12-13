#include<bits/stdc++.h>
using namespace std;
int n,s,v[110],i,j;
class BinPacking
{
	public:
		int minBins(vector<int>a)
		{
			n=a.size();sort(a.begin(),a.end());
			for(i=n-1;~i;i--)if(a[i]>100&&!v[i])
			{
				v[i]=1;n--;s++;
				for(j=i;~j;j--)if(!v[j]&&a[i]+a[j]<=300)
				{
					v[j]=1;n--;
					break;
				}
			}
			return s+(n+2)/3;
		}
};
