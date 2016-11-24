#include<cmath>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const double pi=acos(-1),eps=1e-12;
bool filter(const double &a){
	if (a>eps) return true;
	else if (a<-eps) return true;
	else return false;
}

struct cir{
	double x,y,r;
};

class CircusTents{
	static const int maxn=55;
	cir nod[maxn];
	double use[maxn<<2];
	int top,n;
	
	double repi(double a){
		while(a>pi) a-=2*pi;
		while(a<-pi) a+=2*pi;
		return a;
	}
	
	double sqr(const double &a){return a*a;}
	
	double ask(double theta,cir &t){
		cir &s=nod[0];
		double x=s.x+cos(theta)*s.r,y=s.y+sin(theta)*s.r;
		double d=sqr(x-t.x)+sqr(y-t.y),
		d1=sqr(x-s.x)+sqr(y-s.y),d2=sqr(t.x-s.x)+sqr(t.y-s.y);
		
		if (d+d1<=d2) return sqrt(d)-t.r;
		double t1,t2,del,dis;
		dis=sqr(t.x-s.x)+sqr(t.y-s.y);
		del=acos(s.r/sqrt(dis));
		t1=atan2(t.y-s.y,t.x-s.x);
		t2=repi(t1+del);
		t1=repi(t1-del);
		
		return min(min(abs(theta-t1),2*pi-abs(theta-t1)),min(abs(theta-t2),2*pi-abs(theta-t2)))*
		s.r+sqrt(dis-sqr(s.r))-t.r;
	}
	
	double getans(double theta){
		double ret=1e100;
		for (int i=1;i<n;++i) ret=min(ret,ask(theta,nod[i]));
		return ret;
	}
	
	double solve(double l,double r){
		double a,b,t;
		while(filter(r-l)){
			t=(r-l)*10000/20001;
			a=l+t;
			b=r-t;
			if (getans(a)<getans(b)) l=a;
			else r=b;
		}
		return getans(l);
	}
	
	public:
		double findMaximumDistance(vector<int> x, vector<int> y, vector<int> r){
			n=x.size();
			for (int i=0;i<n;++i) nod[i].x=x[i],nod[i].y=y[i],nod[i].r=r[i];
			for (int i=1;i<n;++i){
				use[top++]=atan2(nod[i].y-nod[0].y,nod[i].x-nod[0].x);
				use[top]=repi(use[top-1]+pi);
				++top;
			}
			double ans=0;
			sort(use,use+top);
			ans=max(ans,solve(-pi,use[0]));
			use[top]=pi;
			for (int i=1;i<=top;++i)
				ans=max(ans,solve(use[i-1],use[i]));
			return ans;
		}
};
