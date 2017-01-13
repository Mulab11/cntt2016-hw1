#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

bool v[40];
int size[40];
double dp[40][40][40][2],dp2[40][40][2];
vi e[40];

void dfs(int k)
{
	v[k]=1;size[k]=1;
	dp[k][1][0][1]=dp[k][0][0][0]=0.5;
	for (int i=0;i<e[k].size();i++)
		if (!v[e[k][i]])
		{
			dfs(e[k][i]);
			for (int j=0;j<=size[k]+size[e[k][i]];j++)
				for (int l=0;l<size[k]+size[e[k][i]];l++)
					for (int p=0;p<2;p++)
					{
						dp2[j][l][p]=dp[k][j][l][p];
						dp[k][j][l][p]=0;
					}
			for (int j=0;j<=size[k];j++)
				for (int l=0;l<size[k];l++)
					for (int x=0;x<2;x++)
						for (int p=0;p<=size[e[k][i]];p++)
							for (int q=0;q<size[e[k][i]];q++)
								for (int y=0;y<2;y++)
									dp[k][j+p][l+q+(x==0&&y==1)][x]+=dp2[j][l][x]*dp[e[k][i]][p][q][y];
			size[k]+=size[e[k][i]];
		}
}	

struct CentaurCompany 
{
    double getvalue(vector <int> a, vector <int> b)
    {
    	int n=a.size()+1;
    	for (int i=0;i<n-1;i++)
    	{
    		e[a[i]].pb(b[i]);e[b[i]].pb(a[i]);
    	}
    	memset(dp,0,sizeof(dp));
    	dfs(1);
    	double ans=0;
    	for (int i=0;i<=n;i++)
    		for (int j=0;j<n;j++)
    			for (int k=0;k<2;k++)
 					ans=ans+dp[1][i][j][k]*max(0,2*(j+(k==1)-1)-i);
    	return ans*2;
    }
};
