#include<bits/stdc++.h>
using namespace std;
int n,k,t,i,ans=999,r,c[2],j,f[320][2];
string S,T;
class FlippingBitsDiv1
{
	public:
		int getmin(vector<string>s,int m)
		{
			for(i=0;i<s.size();i++)S+=s[i];
			n=S.size();
			k=n/m;
			if(k<m)for(t=0;t<(1<<k);t++)//Meet in the middle
			{
				T=S;
				for(i=r=0;i<k;i++)if(t>>i&1)for(r++,j=0;j<i*m+m;j++)T[j]^=1;
				for(i=0;i<m;r+=min(c[0],c[1]),i++)for(c[0]=c[1]=j=0;j<=k;j++)if(j*m+i<n)c[T[j*m+i]&1]++;
				ans=min(ans,r);
			}
			else for(t=0;t<(1<<m);t++)
			{
				memset(f,9,sizeof(f));
				f[0][0]=0;f[0][1]=1;
				for(i=0;i<k;i++)
				{
					for(j=r=0;j<m;j++)if(S[j+i*m]-48!=(t>>j&1))r++;
					f[i+1][0]=min(f[i][1],f[i][0])+r;
					f[i+1][1]=min(f[i][1],f[i][0]+2)+(m-r);
				}
				for(r=j=0;j+k*m<n;j++)if(S[j+k*m]-48!=(t>>j&1))r++;
				ans=min(ans,min(f[k][0],f[k][1])+r); 
			}
			return ans;
		}
};
