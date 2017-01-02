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

typedef long long ll;
const int mod=1000000007;

int m,w[3],id[13][13],d[85][2];

struct matrix
{
	int d[85][85];
}a,b,c;

//matrix multiplication
matrix operator *(matrix a,matrix b)
{
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++)
		{
			c.d[i][j]=0;
			for (int k=1;k<=m;k++) c.d[i][j]=(ll(a.d[i][k])*b.d[k][j]+c.d[i][j])%mod;
		}
	return c;
}

struct ConversionMachine 
{
    int countAll(string word1, string word2, vector <int> costs, int maxCost)
    {
    	int n=word1.size();
    	m=1;
    	for (int i=0;i<=n;i++)
    		for (int j=0;i+j<=n;j++)
    		{
    			d[m][0]=i;d[m][1]=j;
    			id[i][j]=m++;
    		}
    	for (int i=0;i<n;i++)
    	{
    		int x=word1[i]-'a',y=word2[i]-'a',s=0;
    		while (x!=y)
    		{
    			maxCost-=costs[x];
    			if (maxCost<0) return 0;
    			x=(x+1)%3;s++;
    		}
    		w[s]++;
    	}
    	for (int i=1;i<=m;i++)
    		for (int j=1;j<=m;j++)
    		{
    			a.d[i][j]=0;
    			b.d[i][j]=(i==j);
    		}
    	for (int i=1;i<m;i++)
    	{
    		int v[3];
    		v[2]=d[i][0];v[1]=d[i][1];v[0]=n-d[i][0]-d[i][1];
    		for (int j=0;j<3;j++)
    		{
    			v[j]--;v[(j+2)%3]++;
    			a.d[i][id[v[2]][v[1]]]=v[j]+1;
    			v[j]++;v[(j+2)%3]--;
    		}
    	}
    	a.d[1][m]=1;a.d[m][m]=1;
    	int T=maxCost/(ll(costs[0])+costs[1]+costs[2])*3+w[2]*2+w[1]+1;//we can operate at most T times
    	while (T)
    	{
    		if (T&1) b=b*a;
    		a=a*a;T>>=1;
    	}
    	return b.d[id[w[2]][w[1]]][m];
    }
};
