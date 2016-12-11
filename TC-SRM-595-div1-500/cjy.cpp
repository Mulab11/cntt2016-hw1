#include<bits/stdc++.h>
using namespace std;
int g[2555][2555],f[2555],n,i,j,k,x;
long long e;
string s;
class LittleElephantAndRGB
{
	public:
		long long getNumber(vector<string>S,int m)
		{
			for(i=0;i<S.size();i++)s+=S[i];
			x=n=s.size();
			for(i=n-1;~i;i--)
			{
				s[i]=='G'?k++:k=0;
				if(k>=m)x=i+m-1,k=m;else if(k)g[i][k]=x+1-i-k;else g[i][k]=g[i+1][k]+n-i;
				for(j=m-1;j;j--)g[i][j]+=g[i+1][j]+(j<k);
				f[i]=f[i+1]+n-x;
			}
			for(i=0;i<n;i++)for(j=m-1;~j;j--)g[i][j]+=g[i][j+1];
			for(i=0;i<n;i++)for(k=x=0,j=i;j<n;j++)
			{
				s[j]=='G'?k++:k=0;
				if(k>=m)x=1;
				if(x)e+=(n-1-j)*(n-j)/2;else e+=f[j+1]+g[j+1][m-k];
			}
			return e;
		}
};
