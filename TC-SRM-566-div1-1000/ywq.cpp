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

const int mod=100007;
const double pi=acos(-1.0);

struct point
{
    double x,y;
    point(double x0=0,double y0=0) {x=x0;y=y0;}
    point operator -(point a)const {return point(x-a.x,y-a.y);}
}a[230],b[55];

int n,m;
bool w0[130],w1[130];
bool ok[230][230];
int h[230][230][2],dp[230][230];
ll mask[230][230];

double cross(point a,point b)
{
    return a.x*b.y-a.y*b.x;
};

struct FencingPenguins 
{
    int countWays(int numPosts, int radius, vector <int> x, vector <int> y, string color)
    {
        n=numPosts;m=x.size();
        for (int i=0;i<m;i++) b[i]=point(x[i],y[i]);
        for (int i=0;i<n;i++)
        {
            a[i].x=radius*cos(2*pi*i/n);
            a[i].y=radius*sin(2*pi*i/n);
        }
        for (int i=0;i<n;i++)
            for (int j=i+1;j<n;j++)
            {
                for (int c=0;c<128;c++) w0[c]=w1[c]=0;
                for (int k=0;k<m;k++)
                {
                    double t=cross(a[j]-a[i],b[k]-a[i]);
                    if (t>0) w0[int(color[k])]=1; else w1[int(color[k])]=1;
                }
                ok[i][j]=1;
                for (int c=0;c<128;c++) if (w0[c]&&w1[c]) {ok[i][j]=0;break;}
                ok[j][i]=ok[i][j];
            }
        for (int i=0;i<n;i++)
        	for (int j=0;j<n;j++)
        	{
        		mask[i][j]=0;
        		if (i!=j) for (int k=0;k<m;k++) if (cross(a[j]-a[i],b[k]-a[i])>0) mask[i][j]|=(1ll<<k);
        	}
    	for (int i=0;i<n;i++)
    		for (int j=0;j<m;j++)
    			if (cross(b[j]-a[i],a[(i+1)%n]-a[i])>=-(1e-9)) return 0;
        for (int i=0;i<n;i++) //enumerate the end point
        {
        	h[i][i][0]=1;
        	for (int j=i-1;j>=0;j--)
        		for (int k=j+1;k<=i;k++)
        		{
        			if (!ok[j][k]) continue;
        			if (k-j==2&&mask[k][j]) continue;
        			if (k-j>2&&(mask[k][j]&mask[j+1][k-1])) continue;
        			for (int p=0;p<2;p++)
        				if (h[i][k][p])
        				{
        					int t,np;
        					if (mask[k][j]) t=dp[j+1][k-1]; else t=1;
        					if (mask[j][k]&mask[k][i]&mask[i][j]) np=1; else np=p;
        					h[i][j][np]=(ll(h[i][k][p])*t+h[i][j][np])%mod;
        				}
        		}
        	for (int j=0;j<i;j++)
        	{
        		if (!ok[j][i]) h[i][j][1]=0;
        		for (int k=j+1;k<i;k++)
        		{
        			if (!ok[k][i]) continue;
        			if (mask[j][k-1]&mask[k-1][i]&mask[i][j]) continue;
					if (mask[k-1][k]&mask[k][i]&mask[i][k-1]) continue;
        			int t=1;
        			if (mask[k-1][j]) t=dp[j][k-1];
        			h[i][j][1]=(ll(h[i][k][1])*t+h[i][j][1])%mod;
        		}
        	}
        	for (int j=i;j>=0;j--)
        	{
        		dp[j][i]=0;
        		for (int k=i;k>j;k--) if ((!(mask[j][k]&mask[k][i]&mask[i][j]))&&(!mask[i][k])) dp[j][i]=(dp[j][i]+h[k][j][1])%mod;
        	}
    	}
        return dp[0][n-1];			
    }
};
