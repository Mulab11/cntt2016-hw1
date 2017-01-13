#include<bits/stdc++.h>
#define V vector<int>
using namespace std;
int n,m,i,j,f[55][55],c[55],v[55],s;
int dfs(int x){for(int i=1;i<=m;i++)if(f[x][i]&&!v[i])if(v[i]=1,!c[i]||dfs(c[i]))return c[i]=x,1;return 0;}
class PointyWizardHats
{
	public:
		int getNumHats(V h,V r,V H,V R)
		{
			for(n=h.size(),m=H.size();i<n;i++)for(j=0;j<m;j++)if(r[i]<R[j]&&h[i]*R[j]>H[j]*r[i])f[i+1][j+1]=1;
			for(i=1;i<=n;i++)memset(v,0,sizeof(v)),s+=dfs(i);
			return s;
		}
};
