#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;
#define MAXN 51
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct WallGameDiv1
{
	int mp[MAXN][MAXN];
	int n,m;
	int f[MAXN][MAXN][MAXN][MAXN];
	int s[MAXN];
	int play(vector<string>_mp)
	{
		int i,j,len,l;
		n=_mp.size();
		m=_mp[0].size();
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				mp[i][j]=_mp[i-1][j-1]-'0';
			}
		}
		for(i=n-1;i;i--)
		{
			for(len=m-1;~len;len--)
			{
				for(l=1;l+len-1<=m&&l<=m;l++)
				{
					for(j=1;j<=m;j++)
					{
						s[j]=s[j-1]+mp[i][j];
						if(j<l||j>=l+len)
						{
							f[i][j][l][len]=max(f[i+1][j][j][0],f[i+1][j][j][1])+mp[i+1][j];
						}
					}
					for(j=l;j<l+len;j++)
					{
						f[i][j][l][len]=INF;
						if(l!=1)
						{
							int t=f[i][l-1][l][len];
							if(!(l==2&&l+len-1==m))
							{
								t=max(t,f[i][l-1][l-1][len+1]);
							}
							f[i][j][l][len]=min(f[i][j][l][len],t+s[j-1]-s[l-2]);
						}
						if(l+len-1!=m)
						{
							int t=f[i][l+len][l][len];
							if(!(l==1&&l+len==m))
							{
								t=max(t,f[i][l+len][l][len+1]);
							}
							f[i][j][l][len]=min(f[i][j][l][len],t+s[l+len]-s[j]);
						}
					}
				}
			}
		}
		int ans=INF;
		for(i=1;i<=m;i++)
		{
			ans=min(ans,max(f[1][i][i][0],f[1][i][i][1])+mp[1][i]);
		}
		return ans;
	}
};