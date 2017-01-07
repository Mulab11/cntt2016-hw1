#include<cstdio>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
int n,m;
int f[111]={},g[111]={};
int l[222222]={},r[222222]={};//不包含边界
int ll[222222]={},rr[222222]={};//包含边界
int minn=333333333,maxx=0;
bool check2(int a,int b,int c,int d)
{
	return (b<=c&&(c>a||d>b));
}
bool check(int a,int b,int c,int d,int aa,int bb,int cc,int dd)
{
	if(aa>cc||bb>dd)return false;
	if(a==c&&b==d)return false;
	return check2(aa,b,cc,d)||check2(aa,b,c,dd)||check2(a,bb,cc,d)||(a,bb,c,dd);
}
void update0(int a,int b,int c)
{
	l[a]=b+1,r[b]=c-1;
	ll[a]=b,rr[b]=c;
	return;
}
void update1(int a,int b,int c,int d)
{
	if(a>c)
		swap(a,c),swap(b,d);
	for(int i=a;i<=c;i++)
	{
		double temp=1.0*(d-b)/(c-a)*(i-a)+b;
		l[i]=(int)(temp+1.000000001);
		ll[i]=(int)(temp+0.999999999);
		if(i==a||i==c)
			ll[i]=l[i];
	}
}
void update2(int a,int b,int c,int d)
{
	if(a>c)
		swap(a,c),swap(b,d);
	for(int i=a;i<=c;i++)
	{
		double temp=1.0*(d-b)/(c-a)*(i-a)+b;
		r[i]=(int)(temp-0.000000001);
		rr[i]=(int)(temp+0.000000001);
		if(i==a||i==c)
			rr[i]=r[i];
	}
}
class ConvexPolygonGame
{
public:
	string winner(vector <int> X, vector <int> Y)
	{
		n=X.size();
		for(int i=0;i<n;i++)
			f[i]=X[i];
		for(int i=0;i<n;i++)
			g[i]=Y[i];
		f[n]=f[0],g[n]=g[0];
		for(int i=0;i<=n;i++)
			f[i]+=100000,g[i]+=100000;
		for(int i=0;i<n;i++)
			if(f[i]==f[i+1])
				update0(f[i],g[i],g[i+1]);
			else if(f[i]<f[i+1])
				update1(f[i],g[i],f[i+1],g[i+1]);
			else
				update2(f[i],g[i],f[i+1],g[i+1]);
		for(int i=0;i<n;i++)
		{
			if(f[i]>maxx)maxx=f[i];
			if(f[i]<minn)minn=f[i];
		}
		string codeforces="Petya";
		for(int i=minn;i<maxx;i++)
			if(check(l[i],l[i+1],r[i],r[i+1],ll[i],ll[i+1],rr[i],rr[i+1]))
				codeforces="Masha";
		return codeforces;
	}
};
