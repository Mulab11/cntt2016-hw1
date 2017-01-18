#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<map>
#define N 60
#define dd double
#define ll long long
#define eps 1e-7
#define mp make_pair
using namespace std;
int n,c1,c2;
map<pair<int,int>,bool>vi;
struct ma
{int x,y;}f[N],g[N];
struct ConvexPolygonGame
{
string winner(vector<int> a, vector<int> b)
{
	n=a.size();
	for(int i=0;i<n;i++) vi[mp(a[i],b[i])]=true;
	int l=0,r=n-1;
	for(int i=1;i<n;i++) if(a[i]<a[l]) l=i;
	for(int i=n-2;i>=0;i--) if(a[i]>a[r]) r=i;
	int o=l;
	while(o!=r) g[++c2]=(ma)
	{a[o],b[o]},(++o)%=n;
	g[++c2]=(ma)
	{a[o],b[o]};
	o=l;
	while(o!=r) f[++c1]=(ma)
	{a[o],b[o]},o=(o-1+n)%n;
	f[++c1]=(ma)
	{a[o],b[o]};
	bool flag=false,now2=false;
	int n1=1,n2=1,nx=1e9,ny,dx=1e9,dy;
	for(int i=a[l];i<=a[r];i++)
	{
		int p,q,s;
		while(f[n1].x<i) n1++;
		while(g[n2].x<i) n2++;
		if(i==a[l])
		{
			p=q=f[1].y;
			if(f[2].x==i) q=f[2].y;
			if(g[2].x==i) q=g[2].y;
			if(p<q) swap(p,q);
		}
		else if(i==a[r])
		{
			p=f[n1].y;
			q=g[n2].y;
			if(p<q) swap(p,q);
		}
		else
		{
			dd A=f[n1-1].y+(dd)(f[n1].y-f[n1-1].y)/(f[n1].x-f[n1-1].x)*(i-f[n1-1].x);
			dd B=g[n2-1].y+(dd)(g[n2].y-g[n2-1].y)/(g[n2].x-g[n2-1].x)*(i-g[n2-1].x);
			p=floor(A);
			q=ceil(B);
		}
		if(vi[mp(i,p)]) p--;
		if(vi[mp(i,q)]) q++;
		s=p-q+1;
		if(s>=2)
		{
			if(nx!=1e9||now2)
			{
				flag=true;
				break;
			}
			now2=true;
		}
		if(s==1)
		{
			if(now2)
			{
				flag=true;
				break;
			}
			if(nx==1e9) nx=i,ny=p;
			else if(dx==1e9) dx=i-nx,dy=p-ny;
			else if((ll)dx*(p-ny)!=(ll)dy*(i-nx))
			{
				flag=true;
				break;
			}
		}
	}
	return flag?"Masha":"Petya";
}
};