#include <bits/stdc++.h>

using namespace std;

const double pi=acos(-1);
struct orz{
	int x,y,r;
}c[55];
double aa[555];
struct seg{
	double l,r;
}q[555];
bool in(double x,double l,double r){//判断是否在区间内 
	if(l<=r)return l<=x&&x<=r;
	else return x>=l||x<=r; 
}
int n,R;
double qx[55];
double dist(double a,double b){
	return sqrt(a*a+b*b);
}
void ga(double&x){//把x变到[-pi,pi]内 
	if(x>pi)x-=2*pi;
	if(x<-pi)x+=2*pi;
}
bool work(double x){
	int tot=0,cnt=0;
	for(int i=1;i<=n;++i){
		double l,r,ang,d;
		if(x+c[i].r<=qx[i]){
			d=(1.*R*R+1.*c[i].x*c[i].x+1.*c[i].y*c[i].y-(x+c[i].r)*(x+c[i].r))/(2.*R*dist(c[i].x,c[i].y));
			if(x+c[i].r+R<=dist(c[i].x,c[i].y))l=-pi,r=pi;//整个圆 
			else {
				ang=acos(d);
				l=atan2(c[i].y,c[i].x)+ang;
				r=atan2(c[i].y,c[i].x)-ang;//区间 
			}
		} else {
			d=(x+c[i].r-qx[i])/R;
			ang=atan(qx[i]/R)+d;
			l=atan2(c[i].y,c[i].x)+ang;
			r=atan2(c[i].y,c[i].x)-ang;//区间 
		}
		ga(l);ga(r);q[++tot].l=l;q[tot].r=r;aa[++cnt]=l;aa[++cnt]=r;
	}
	for(int i=1;i<=cnt;++i){
		double t=aa[i];
		bool flag=1;
		for(int j=1;j<=tot;++j)if(!in(t,q[j].l,q[j].r)){flag=0;break;}//判断是否在所有区间内 
		if(flag)return 1;
	}
	return 0;
}
double erf(){//二分 
	double l=0,r=1000000,mid;
	for(int i=1;i<=n;++i){
		double d=dist(c[i].x,c[i].y),e;
		qx[i]=sqrt(d*d-1.*R*R);//切线长 
		e=atan(qx[i]/R);
		r=min(r,qx[i]+(pi-e)*R-c[i].r);
	}
	for(int _=1;_<=100;++_){
		mid=(l+r)/2;
		if(work(mid))l=mid;
		else r=mid;
	}
	return l;
}

class CircusTents {
public:
	double findMaximumDistance(vector <int> x, vector <int> y, vector <int> r) {
		n=x.size()-1;R=r[0];
		for(int i=1;i<=n;++i)c[i].x=x[i]-x[0],c[i].y=y[i]-y[0],c[i].r=r[i];//平移一下方便计算 
		return erf();
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
