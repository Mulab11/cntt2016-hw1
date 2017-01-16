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
int a[27][13],g[27][27],m[27];

struct History 
{
    string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries)
    {
    	int n=dynasties.size();
    	for (int i=0;i<n;i++)
    	{
    		int t=0,l=dynasties[i].size();
    		m[i]=0;
    		for (int j=0;j<=l;j++)
    			if (j==l||dynasties[i][j]==' ')
    			{
    				a[i][m[i]++]=t;
    				t=0;
    			}
    			else
    				t=t*10+dynasties[i][j]-48;
    	}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			if (i==j) g[i][j]=0; else g[i][j]=inf;
    	static string ss="";
    	for (int i=0;i<battles.size();i++) ss+=battles[i];
    	for (int i=0;i<ss.size();i+=6)
    	{
    		int x0=ss[i]-'A',x1=ss[i+1]-'0';
    		int y0=ss[i+3]-'A',y1=ss[i+4]-'0';
    		g[x0][y0]=min(g[x0][y0],a[y0][y1+1]-a[x0][x1]-1);
    		g[y0][x0]=min(g[y0][x0],a[x0][x1+1]-a[y0][y1]-1);
    	}
    	for (int k=0;k<n;k++)
    		for (int i=0;i<n;i++)
    			for (int j=0;j<n;j++)
    				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
    	string ans="";
    	for (int i=0;i<queries.size();i++)
    	{
    		int x0=queries[i][0]-'A',x1=queries[i][1]-'0';
    		int y0=queries[i][3]-'A',y1=queries[i][4]-'0';
    		if (a[x0][x1]-a[y0][y1+1]+1<=g[y0][x0]&&a[y0][y1]-a[x0][x1+1]+1<=g[x0][y0]) ans+='Y'; else ans+='N';
    	}
    	return ans;
    }
};
