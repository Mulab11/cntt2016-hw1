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

struct vec
{
	int x,y;
	vec(int x0=0,int y0=0) {x=x0;y=y0;}
	vec operator +(vec a)const {return vec(x+a.x,y+a.y);}
	vec operator -(vec a)const {return vec(x-a.x,y-a.y);}
}z[30];

ll cross(vec a,vec b) {return ll(a.x)*b.y-ll(a.y)*b.x;}

int l[300010],r[300010];

vec f(int n,int x)
{
	x%=(4*n);
	if (x<n) return vec(x,0);
	if (x<2*n) return vec(n,x-n);
	if (x<3*n) return vec(3*n-x,n);
	return vec(0,4*n-x);
}

int calc1(int n,int k,int l0,int r0)
{
	int t=l[k%(4*n)];if (k>=4*n) t+=4*n;
	if (t<l0) return 0;
	if (t>r0) return r0-l0+1-(k==l0);
	return t-l0+1-(k==l0);
}

int calc2(int n,int k,int l0,int r0)
{
	int t=r[k%(4*n)];if (k<4*n) t-=4*n;
	if (t>r0) return 0;
	if (t<l0) return r0-l0+1-(k==r0);
	return r0-t+1-(k==r0);
}

struct EnclosingTriangle 
{
    long long getNumber(int m, vector <int> x, vector <int> y)
    {
    	int n=x.size();
    	for (int i=0;i<n;i++) z[i]=vec(x[i],y[i]);
    	for (int i=0;i<4*m;i++)
    	{
    		vec t1=f(m,i);
    		int l0=i+1,r0=i+4*m-1;
    		while (l0<=r0)
    		{
    			int mid=(l0+r0)>>1;
    			vec t2=f(m,mid);
    			bool ok=1;
    			for (int j=0;j<n;j++)
    				if (cross(t2-t1,z[j]-t1)<0LL) ok=0;
    			if (ok) l0=mid+1; else r0=mid-1;
    		}
    		l[i]=r0;
    		l0=i+1;r0=i+4*m-1;
    		while (l0<=r0)
    		{
    			int mid=(l0+r0)>>1;
    			vec t2=f(m,mid);
    			bool ok=1;
    			for (int j=0;j<n;j++)
    				if (cross(t2-t1,z[j]-t1)>0LL) ok=0;
    			if (ok) r0=mid-1; else l0=mid+1;
    		}
    		r[i]=l0;
    	}
    	ll ans=0;
    	for (int j=1;j<=l[0];j++) ans+=calc1(m,j,r[0],4*m-1);
    	ll tmp=ans;
    	for (int i=1;i<4*m;i++)
    	{
    		for (int j=r[i-1];j<r[i];j++) tmp-=calc2(m,j,i,l[i-1]);
    		tmp+=calc2(m,i+4*m-1,i,l[i-1]);
    		tmp-=calc1(m,i,r[i],i+4*m-1);
    		for (int j=l[i-1]+1;j<=l[i];j++) tmp+=calc1(m,j,r[i],i+4*m-1);
    		ans+=tmp;
    	}
    	return ans/3;
    }	
};
