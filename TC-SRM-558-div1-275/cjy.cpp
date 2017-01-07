#include<bits/stdc++.h>
using namespace std;
int f[55],v[55],i,j,l=1,k,c,n,s=1e9;
class Stamp
{
	public:
		int getMinimumCost(string C,int A,int B)
		{
			for(n=C.size();l<=n;s=min(s,f[n]+l*A),l++)
			{
				for(v[i=0]=l;i<n;i++)if(v[i]==l)for(c=0,j=i;j<n;j++)
				{
					if(C[j]!='*'){if(c&&c!=C[j])break;c=C[j];}
					if(k=f[i]+(j-i+l)/l*B,j-i+1>=l&&(v[j+1]<l||f[j+1]>k))f[j+1]=k,v[j+1]=l;
				}
			}
			return s;
		}
};
