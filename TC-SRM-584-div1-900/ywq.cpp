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

const int inf=1000000000;
string s;
int g[110][110],dp[1<<10][110];
bool v[110];

struct FoxTheLinguist 
{
    int minimalHours(int n, vector <string> courseInfo)
    {
    	int N=n*10+1;
    	for (int i=0;i<N;i++)
    		for (int j=0;j<N;j++)
    			g[i][j]=inf;
    	for (int i=0;i<n;i++) g[0][i*10+1]=0;
    	s="";
    	for (int i=0;i<courseInfo.size();i++) s+=courseInfo[i];
    	for (int i=0;i<s.size();i+=12)
    	{
    		int x=(s[i]-'A')*10+s[i+1]-'0'+1;
    		int y=(s[i+4]-'A')*10+s[i+5]-'0'+1;
    		int z=0;
    		for (int j=7;j<11;j++) z=z*10+s[i+j]-'0';
    		g[x][y]=min(g[x][y],z);
    	}
    	for (int i=0;i<n;i++)
    		for (int j=1;j<10;j++)
    			g[i*10+j+1][i*10+j]=0;
    	for (int i=1;i<(1<<n);i++) 
    	{
    		for (int k=0;k<N;k++) dp[i][k]=inf;
    		for (int j=0;j<n;j++)
    			if (i&(1<<j))
    			{
    				if (i==(1<<j))
    					dp[i][(j+1)*10]=0;
    			}
    		for (int j=1;j<i;j++)
    			if ((i&j)==j)
    				for (int k=0;k<N;k++)
    					dp[i][k]=min(dp[i][k],dp[j][k]+dp[i^j][k]);
    		memset(v,0,sizeof(v));
    		for (int j=1;j<N;j++)
    		{
    			int p=-1,mi=inf;
    			for (int k=0;k<N;k++) if (dp[i][k]<=mi&&!v[k]) {p=k;mi=dp[i][k];}
    			v[p]=1;
    			for (int k=0;k<N;k++) dp[i][k]=min(dp[i][k],g[k][p]+mi);
    		}
    	}
    	if (dp[(1<<n)-1][0]==inf) return -1; else return dp[(1<<n)-1][0];
    }
};
