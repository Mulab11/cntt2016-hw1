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

const int di[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

vi e[2510];
int n,m,cnt;
bool v[2510];
int size[2510],q[2510],d[310][2510],a[310];
double ans1,ans2,f[310],g[310];

int id(int x,int y) {return x*m+y;}

void dfs(int x)
{
	v[x]=1;
	for (int i=0;i<e[x].size();i++)
		if (!v[e[x][i]])
		{
			dfs(e[x][i]);
			ans1+=1-f[size[e[x][i]]]-f[cnt-size[e[x][i]]];
			size[x]+=size[e[x][i]];
		}
}

struct Orienteering 
{
    double expectedLength(vector <string> field, int K)
    {
    	n=field.size();m=field[0].size();cnt=0;

        //add edges

    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    		{
    			int x=id(i,j);
    			if (field[i][j]=='#') continue;
    			if (field[i][j]=='*') {a[++cnt]=x;size[x]=1;}
    			for (int k=0;k<4;k++)
    			{
    				int ti=i+di[k][0],tj=j+di[k][1];
    				if (ti>=0&&ti<n&&tj>=0&&tj<m&&field[ti][tj]!='#') e[x].pb(id(ti,tj));
    			}
    		}

        //calculate the expected value of the sum of all edges' length

    	ans1=0;
    	f[cnt]=1;for (int i=cnt;i;i--) f[i-1]=f[i]/i*(i-K);
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (field[i][j]!='#')
    			{
    				dfs(id(i,j));break;
    			}

        //calculate the expected value of the tree's diameter

    	for (int i=1;i<=cnt;i++)
    	{
    		int f=1,r=1;q[1]=a[i];
    		for (int j=0;j<n*m;j++) d[i][j]=n*m;d[i][a[i]]=0;
    		while (f<=r)
    		{
    			int x=q[f++];
    			for (int j=0;j<e[x].size();j++)
    				if (d[i][e[x][j]]==n*m)
    				{
    					d[i][e[x][j]]=d[i][x]+1;
    					q[++r]=e[x][j];
    				}
    		}
    	}
        g[cnt-2]=1;
        for (int i=cnt-2;i;i--) g[i-1]=g[i]/i*(i-K+2);
        ans2=0;
    	for (int i=1;i<=cnt;i++)
    		for (int j=i+1;j<=cnt;j++)
    		{
    			int t=0;
    			for (int k=1;k<=cnt;k++)   			
    			{
    				if (d[k][a[j]]>d[i][a[j]]) continue;
    				if (d[k][a[j]]==d[i][a[j]]&&k<=i) continue;
    				if (d[i][a[k]]>d[i][a[j]]) continue;
    				if (d[i][a[k]]==d[i][a[j]]&&k<=j) continue;
    				t++;
    			}
    			ans2+=d[i][a[j]]*g[t];
    		}
        ans2=ans2*K*(K-1)/cnt/(cnt-1);
        return ans1*2-ans2;
    }
};
