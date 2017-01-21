// BEGIN CUT HERE

// END CUT HERE
#line 5 "Constellation.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define N 55
typedef pair<int,int> Point;
inline int getSign(ll x){return x>=0?x>0:-1;}
inline ll operator *(const Point &a,const Point &b){return a.first*b.second-b.first*a.second;}
inline ll getS(const Point &a,const Point &u,const Point &v){return u*v+v*a+a*u;}

class Constellation{
	pair<pair<int,int>,int> a0[N];
	pair<int,int> a[N];
	double p[N];
	int n;
	public:
	double expectation(vector <int> x, vector <int> y, vector <int> prob){
		#define X(t) (a[t].first)
		#define Y(t) (a[t].second)
		n=x.size();
		for (int i=0;i<n;++i) a0[i]=make_pair(make_pair(x[i],y[i]),prob[i]);
		sort(a0,a0+n);
		for (int i=0;i<n;++i) a[i]=a0[i].first,p[i]=(double)a0[i].second/1000.0;
		double ret=0;
		for (int i=0;i<n;++i)
			for (int u=i+1;u<n;++u)for (int v=u+1;v<n;++v){
				double w=p[i]*p[u]*p[v];
				ll Si=getS(a[i],a[u],a[v]),Sj;
				if (!Si) continue;
				for (int j=0;j<n;++j)if (j!=i&&j!=u&&j!=v)
					if (j<i || (getSign(Sj=getS(a[j],a[u],a[v]))!=getSign(Si)&&Sj) || 
					(!Sj && ((X(u)<X(j)&&X(j)<X(v)) || (X(u)==X(v)&&u<j&&j<v))))
						w*=1.0-p[j];
				ret+=w*fabs(Si)/2.0;
			}
		return ret;
	}
};

//this is for test
/*
int main(){
	Constellation test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
