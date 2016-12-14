#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int a[111]={},b[111]={},c[111]={},d[111]={},n,m;
bool f[111][111]={};int y[111]={};bool vis[111]={};
int dfs(int x)
{
	vis[x]=1;
	for(int i=1;i<=m;i++)
		if(f[x][i]&&(!y[i]||!vis[y[i]]&&dfs(y[i])))
		{
			y[i]=x;return 1;
		}
	return 0;
}
class PointyWizardHats
{
    public:
        int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius)
        {
            n=topHeight.size();
            m=bottomHeight.size();
			for(int i=1;i<=n;i++)
				a[i]=topHeight[i-1],b[i]=topRadius[i-1];
			for(int i=1;i<=m;i++)
				c[i]=bottomHeight[i-1],d[i]=bottomRadius[i-1];
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					if(b[i]<d[j]&&1LL*a[i]*d[j]>1LL*b[i]*c[j])
						f[i][j]=1;
			int ans=0;
			for(int i=1;i<=n;i++)
			{
				for(int j=0;j<=102;j++)
					vis[j]=0;
				ans+=dfs(i);
			}
			return ans;
		}
};
