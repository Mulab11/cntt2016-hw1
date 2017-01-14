#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
typedef long long LL;
const long double eps=1e-10;
struct point
{
	int x,y;
	point(){}
	point(const int &_x,const int &_y):x(_x),y(_y){}
	point operator+(const point &o)const{return point(x+o.x,y+o.y);}
	point operator-(const point &o)const{return point(x-o.x,y-o.y);}
	LL operator*(const point &o)const{return (LL)x*o.y-(LL)y*o.x;}
}; 

class ConvexPolygonGame
{
	public:
	int n;
	point P[55];
	
	vector<point> inside_point;
	
	bool addpoint(point p)//check if there are 3 points which can form a triangle.
	{
		if(inside_point.size()<2)inside_point.push_back(p);
		point a=inside_point[0],b=inside_point[1];
		if((p-a)*(p-b)==0)
			return 0;
		return 1; 
	} 
	
	string winner(vector<int> X,vector<int> Y)
	{
		//If Masha can make a move, she will win.
		//otherwise she can move to the last situation in one step and will also win.
		//So we need to check it.
		n=X.size();
		for(int i=0;i<n;i++)
			P[i]=point(X[i],Y[i]);
		//Find all points inside the polygon, if they can form a triangle, Masha wins.
		//The number of points can't exceed 200000 untill thay can form a triange.
		for(int p=-100000;p<=100000;p++)//enumerate all x-coordinate.
		{
			LL l=-100000,r=100000;//The range of y is [l,r].
			point a,b;
			for(int i=0;i<n&&l<=r;i++)//Use all side and vetices to update the range.
			{
				a=P[i],b=P[(i+1)%n];
				if(a.x==b.x)//Vertical sides.
				{
					if(a.x==p)
					{
						l=max(l,min(a.y,b.y)+1LL);
						r=min(r,max(a.y,b.y)-1LL);
					}
					else
						if(a.y<b.y&&a.x<p||a.y>b.y&&a.x>p)//no points inside.
							l=r+1;
				}
				else
				{
					//Get the y-coordinate of the intersection.
					long double q=(((long double)b.x-p)*a.y+((long double)p-a.x)*b.y)/(b.x-a.x);
					LL qu,qd;
					qu=qd=(LL)q;
					if(qu+eps<q)qu++;
					if(qd-eps>q)qd--;
					if(a.x<b.x)//Half plane upper the segment.
					{
						l=max(l,qu);
						if(a.x==p)
							l=max(l,a.y+1LL);
						if(b.x==p)
							l=max(l,b.y+1LL);
					}
					else////Half plane under the segment.
					{
						r=min(r,qd);
						if(a.x==p)
							r=min(r,a.y-1LL);
						if(b.x==p)
							r=min(r,b.y-1LL);
					}
				}
			}
			for(int j=l;j<=r;j++)
				if(addpoint(point(p,j)))
					return "Masha";
		}
		return "Petya";
	}
};

