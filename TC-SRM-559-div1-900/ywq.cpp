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

const double pi=acos(-1.0);
struct node
{
	double l,r;
	bool operator <(node a)const {return l<a.l;}
}a[110];

struct CircusTents 
{
    double findMaximumDistance(vector <int> x, vector <int> y, vector <int> r)
    {
    	int n=x.size();
    	for (int i=n-1;i>=0;i--) {x[i]-=x[0];y[i]-=y[0];}
    	double L=0,R=100000;
    	for (int T=1;T<=2000;T++)
    	{
    		double d=(L+R)/2;
    		int cnt=0;
    		for (int i=1;i<n;i++)
    		{
    			double d0=sqrt(double(x[i]*x[i]+y[i]*y[i]));
    			if (r[0]+r[i]+d<d0) continue;
				double d1=sqrt(d0*d0-r[0]*r[0])-r[i]; //the length of the tangent line
				double a0=atan2(double(y[i]),double(x[i]));
				if (d<d1)
				{
					double a1=acos((d0*d0-(r[i]+d)*(r[i]+d)+r[0]*r[0])/(2*d0*r[0]));
					a[++cnt].l=a0-a1;a[cnt].r=a0+a1;
				}
				else
				{
					double a1=atan2(d1+r[i],double(r[0]));
					double d2=d-d1;
					double a2=d2/r[0];
					if (a1+a2>=pi)
					{
						a[++cnt].l=-1;a[cnt].r=10;
					}
					else
					{
						a[++cnt].l=a0-a1-a2;a[cnt].r=a0+a1+a2;
					}
				}
			}
			int m=cnt;
			for (int i=1;i<=cnt;i++)
				if (a[i].l<0) //turn the circle into a line
				{
					a[++m].l=a[i].l+pi*2;
					a[m].r=a[i].r+pi*2;
				}
			sort(a+1,a+m+1);
			double now=0;
			int k=1;
			while (now<2*pi)
			{
				double t=now;
				while (k<=m&&a[k].l<=now)
				{
					now=max(now,a[k].r);k++;
				}
				if (now<=t) break;
			}
			if (now>=2*pi) R=d; else L=d;
		}
		return (L+R)/2;
    }
};
