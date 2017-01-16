#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL E,a[40],t,x,f,g,s;
string S;
int n,m,i,j,k;//搜索，容斥
void dfs(int k,LL x,int f){if(k==t){for(g=f,i=0;i<n;i++)if(x>>i&1)g*=2;s+=g;}else if(x)dfs(k+1,x,f),dfs(k+1,x&a[k],-f);}
class MapGuessing
{
	public:
		LL countPatterns(string e,vector<string> _)
		{
			for(auto y:_)S+=y;
			for(n=e.size(),m=S.size();i<n;i++)E+=((LL)e[i]-48)<<i;
			for(j=0;j<n;j++)
			{
				for(k=j,i=x=f=g=0;i<m;i++)
				{
					if(S[i]=='<')k--;else if(S[i]=='>')k++;else
					{
						if(x|=1ll<<k,S[i]-48!=(f>>k&1))f^=1ll<<k;
						if((x&E)==f)g=x;
					}
					if(k<0||k>=n)goto Z;
				}
				a[t++]=g;Z:;
			}
			return s=1ll<<n,dfs(0,s-1,-1),s;
		}
};
