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
const double eps=1e-5;
const int inf=1000000000;

struct complex
{
	double x,y;
	complex(double x0=0,double y0=0) {x=x0;y=y0;}
	complex operator +(complex a)const {return complex(x+a.x,y+a.y);}
	complex operator *(complex a)const {return complex(x*a.x-y*a.y,x*a.y+y*a.x);}
};

complex sqrt0(complex a)
{
	double ang=atan2(a.y,a.x)/2;
	double t=a.x*a.x+a.y*a.y;
	if (t<0) t=0; else t=sqrt(sqrt(t));
	return complex(t*cos(ang),t*sin(ang));
}

int n;
complex a[30],b[30],c[30],w[30];
int d[30],ans[30];
vector<int> tmp;

void dft(complex *a)
{
	for (int i=0;i<n;i++)
	{
		b[i]=complex(0.0,0.0);
		for (int j=0;j<n;j++)
			b[i]=b[i]+a[j]*w[i*j%n];
	}
	for (int i=0;i<n;i++) a[i]=b[i];
}

struct SplittingFoxes2 
{
    vector <int> getPattern(vector <int> amount)
    {
    	n=amount.size();
    	for (int i=0;i<n;i++)
    	{
    		w[i].x=cos(2*pi*i/n);
    		w[i].y=sin(2*pi*i/n);
    		a[i]=complex(double(amount[i]),0.0);
    	}
    	dft(a);
    	for (int i=0;i<n;i++) a[i]=sqrt0(a[i]);
    	int m=n/2+1;
   		ans[0]=inf;
    	for (int i=0;i<(1<<m);i++)
    	{
    		for (int j=0;j<n;j++)
  			{
  				c[j]=a[j];
    			if (i&(1<<min(j,n-j)))
    			{
    				c[j].x=-c[j].x;c[j].y=-c[j].y;
    			}
    		}
    		dft(c);
    		for (int j=0;j<n;j++) {c[j].x/=n;c[j].y/=n;}
    		bool ok=1;
    		//for (int j=0;j<n;j++) printf("%.8lf %.3lf\n",c[j].x,c[j].y);puts("");
    		for (int j=0;j<n;j++)
    		{
    			int p=int(c[j].x+0.5);
    			if (fabs(p-c[j].x)>eps||p<0) {ok=0;break;}
    			d[j]=p;
    		}
    		if (ok)
    		{
    			for (int j=0;j<n;j++)
    			{
    				if (d[j]<ans[j]) break;
    				if (d[j]>ans[j]) {ok=0;break;}
    			}
    			if (ok) for (int j=0;j<n;j++) ans[j]=d[j];
    		}
    	}
    	if (ans[0]==inf)
    		tmp.pb(-1);
    	else
    		for (int i=0;i<n;i++) tmp.pb(ans[i]);
    	return tmp;
    }
};
CodeProcessor
