// BEGIN CUT HERE

// END CUT HERE
#line 5 "CircusTents.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define pi acos(-1.0)
#define eps (1e-9)

struct Point{
	double x,y;
	Point(){}
	Point(const double &_x,const double &_y):x(_x),y(_y){}
	double angle(){return atan2(y,x);}
};
inline Point operator -(const Point &u,const Point &v){return Point(u.x-v.x,u.y-v.y);}
inline double dot(const Point &u,const Point &v){return u.x*v.x+u.y*v.y;}
//inline double cross(const Point &u,const Point &v){return u.x*v.y-v.x*u.y;}
inline bool CrossoverPoint(const Point &u,const double &ru,const Point &v,const double &rv,double &l,double &r){
	Point d=v-u;
	double ang=d.angle(),dist2=dot(d,d),tmp=(dist2+ru*ru-rv*rv)/(2.0*sqrt(dist2)*ru);
	if (tmp>=1.0||tmp<=-1.0) return 0;
	tmp=acos(tmp);
	l=ang-tmp;
	r=ang+tmp;
	return 1;
}


const int maxn=55;

class CircusTents{
	int n;
	Point P[maxn];
	double R[maxn];
	vector<pair<double,double> > lmt;
	void add(double l,double r){
		if (l<-pi) lmt.push_back(make_pair(l+pi*2.0,pi));
		if (r>pi) lmt.push_back(make_pair(-pi,r-pi*2.0));
		lmt.push_back(make_pair(max(l,-pi),min(r,pi)));
	}
	bool check(double ans){
		lmt.clear();
		for (int i=1;i<n;++i){
			Point d=P[i]-P[0];
			double dist2=dot(d,d),ri=R[i]+ans,tmp=dist2-R[0]*R[0],l,r;
			if (ri*ri>tmp){
				CrossoverPoint(P[0],R[0],P[i],sqrt(tmp),l,r);
				double ang=(ri-sqrt(tmp))/R[0];
				l-=ang;r+=ang;
				if (r-l>=2.0*pi) return 0;
				add(l,r);
			}
			else if (CrossoverPoint(P[0],R[0],P[i],ri,l,r)) add(l,r);
		}
		sort(lmt.begin(),lmt.end());
		double _last=-pi;
		for (auto j:lmt){
			if (j.first>_last) return 1;
			_last=max(_last,j.second);
		}
		return _last<pi;
	}
	public:
	double findMaximumDistance(vector <int> x, vector <int> y, vector <int> r){
		n=x.size();
		for (int i=0;i<n;++i) P[i]=Point(x[i],y[i]),R[i]=r[i];
		double _l=0,_r=1e5;
		while (fabs(_r-_l)>eps){
			double mid=(_l+_r)/2.0;
			if (check(mid)) _l=mid;
			else _r=mid;
		}
		return _l;
	}
};
