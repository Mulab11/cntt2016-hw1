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

const int mod=1234567891;

int c0,h,n,g[15];
unsigned cc[5000][6];
bool ok[7];

struct matrix
{
	unsigned d[90][90];
}a,b,c,d;

matrix operator *(matrix a,matrix b)
{
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			c.d[i][j]=0;
			for (int k=0;k<n;k++) c.d[i][j]=(ll(a.d[i][k])*b.d[k][j]+c.d[i][j])%mod;
		}
	return c;
}

int calc1(int *a) //find the type of the layer
{
	if (a[0]==a[1]&&a[1]==a[2]&&a[2]==a[3]) return 0;
	if (a[0]==a[1]&&a[0]==a[2]) return 1;
	if (a[0]==a[1]&&a[0]==a[3]) return 1;
	if (a[0]==a[2]&&a[0]==a[3]) return 1;
	if (a[1]==a[2]&&a[1]==a[3]) return 1;
	if (a[0]==a[2]&&a[1]==a[3]) return 2;
	if (a[0]==a[1]&&a[2]==a[3]) return 2;
	if (a[0]==a[3]&&a[1]==a[2]) return 3;
	if (a[0]==a[1]||a[0]==a[2]||a[1]==a[3]||a[2]==a[3]) return 4;
	if (a[0]==a[3]||a[1]==a[2]) return 5;
	return 6;
}

int calc2(int *a)
{
	return (a[0]==a[1])+(a[1]==a[3])+(a[3]==a[2])+(a[2]==a[0]);
}

void dfs(int k,int n)
{
	if (n>c0) return;
	if (k==4)
	{
		int x=calc1(g),y=calc2(g);
		if (y<=h) d.d[0][y*7+x]=(d.d[0][y*7+x]+cc[c0][n])%mod;
		if (ok[x]) return;ok[x]=1;//we should count one type once
	}
	if (k==8)
	{
		int x1=calc1(g),y1=calc2(g);
		int x2=calc1(g+4),y2=calc2(g+4);
		int y3=0;
		for (int i=0;i<4;i++) if (g[i]==g[i+4]) y3++;
		int n0=0;for (int i=0;i<4;i++) n0=max(n0,g[i]);
		for (int i=0;i+y1+y2+y3<=h;i++)
			a.d[(y1+i)*7+x1][(y1+y2+y3+i)*7+x2]=(a.d[(y1+i)*7+x1][(y1+y2+y3+i)*7+x2]+cc[c0-n0][n-n0])%mod;
		return;
	}
	for (int i=1;i<=n;i++)
	{
		g[k]=i;dfs(k+1,n);
	}
	g[k]=n+1;dfs(k+1,n+1);
}

struct TheBrickTowerHardDivOne 
{
    int find(int C, int K, long long H)
    {
    	c0=C;
    	for (int i=0;i<=C;i++)
    	{
    		cc[i][0]=1;
    		for (int j=1;j<=4;j++) cc[i][j]=ll(cc[i][j-1])*(i-j+1)%mod;
    	}
    	h=K;n=7*(h+1)+1;
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    		{
    			a.d[i][j]=0;
    			b.d[i][j]=(i==j);
    		}
    	for (int i=0;i<n;i++) d.d[0][i]=0;
    	dfs(0,0);
    	for (int i=0;i<n;i++) a.d[i][n-1]=1;
    	while (H)
    	{
    		if (H&1) b=b*a;
    		a=a*a;H>>=1;
    	}
    	int ans=0;
    	for (int i=0;i<n-1;i++) ans=(ll(d.d[0][i])*b.d[i][n-1]+ans)%mod;
    	return ans;
    }
};
