#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;

struct point
{
	int x,y;
	point(){}
	point(const int &_x,const int &_y):x(_x),y(_y){}
	point operator+(const point &o)const{return point(x+o.x,y+o.y);}
	point operator-(const point &o)const{return point(x-o.x,y-o.y);}
	LL operator*(const point &o)const{return (LL)x*o.y-(LL)y*o.x;}
};
const int maxn=255555;
class EnclosingTriangle
{
	public:
	int n,m;
	point P[maxn],Q[25];
	int L[maxn],R[maxn];
	LL suml[maxn];
	LL ans;
	
	bool all_on_left(const point &a,const point &b)//check if all red points are on the left of line a->b
	{
		for(int i=0;i<m;i++)
			if((b-a)*(Q[i]-a)<0)return 0;
		return 1;
	}
	
	void workLR()
	{
		for(int i=0,j=0;i<n;i++)//use two-pointer to determine R[i]
		{
			for(;all_on_left(P[i],P[j]);j=(j+1)%n);
			R[i]=(j-i-1+n)%n;
		}
		for(int i=n-1,j=n-1;i>=0;i--)//use two-pointer to determine L[i]
		{
			for(;all_on_left(P[j],P[i]);j=(j-1+n)%n);
			L[i]=(i-j-1+n)%n;
		}
		for(int i=0;i<n;i++)
			suml[i+1]=suml[i]+L[i];
	}
	
	LL SumL(int l,int r)
	{
		if(l<=r)return suml[r+1]-suml[l];
		return suml[n]-suml[l]+suml[r+1];
	}
	
	void solve()
	{
		LL t;
		for(int i=0;i<n;i++)//pick all points P[i] as a vertex of the triangle
		{
			int l=(i-L[i]+n)%n;
			int r=(i+R[i])%n;
			if(L[i]+R[i]+L[l]<n)continue;//can't form a triangle
			int rr=(r+R[r])%n;//another vertex should be in interval [rr,l] (mod n)
			//calculate the sum of the third vertex's interval length
			// length is L[i]-(i-r-1 mod n)
			t=SumL(l,rr);
			int fi=(l-r+n)%n,la=(rr-r+n)%n;
			t-=(LL)(fi+la-2)*(la-fi+1)/2;
			if(l==r)t-=3;//notice: Let x=l=r, and (i,i,x)(i,x,x)(i,x,i) should be ignored 
			ans+=t;
		}
	}
	
	LL getNumber(int m,vector<int> x,vector<int> y)
	{
		this->m=x.size();
		for(int i=0;i<x.size();i++)
			Q[i]=point(x[i],y[i]);
		//Create points
		for(int i=0;i<m;i++)
			P[n++]=point(i,0);
		for(int i=0;i<m;i++)
			P[n++]=point(m,i);
		for(int i=0;i<m;i++)
			P[n++]=point(m-i,m);
		for(int i=0;i<m;i++)
			P[n++]=point(0,m-i);
		//Solve L[i],R[i]
		//L[i] is the greatest number to choose so that polygon i,i-1,i-2,...,i-L[i] (mod n) contains no red points strictly
		//L[i] and R[i] are similar
		workLR();
		ans=0;
		solve();
		return ans/3;
	}
};

