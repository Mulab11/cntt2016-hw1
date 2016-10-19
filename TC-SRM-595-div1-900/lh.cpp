#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=55;

struct point{
	double x,y;
	point (double a=0,double b=0):x(a),y(b){};
	point operator + (const point &a)const{
		return point (x+a.x,y+a.y);
	}
	point operator - (const point &a)const{
		return point (x-a.x,y-a.y);
	}
	double operator * (const point &a)const{
		return x*a.y-y*a.x;
	}
	friend double dist(const point &a){
		return a.x*a.x+a.y*a.y;
	}
	bool operator < (const point &a)const{
		if (x!=a.x) return x<a.x;
		else return y<a.y;
	}
};

class Constellation{
	private:
		double pr[maxn];
		point nod[maxn];
		int n;
	public:
		double expectation(vector <int> x, vector <int> y, vector <int> prob){
			double ans=0;
			n=x.size();
			for (int i=0;i<n;++i){
				nod[i]=point(x[i],y[i]);
				pr[i]=prob[i]/1000.0;
			}
			
			//枚举所有有向边。 
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (i!=j){
				double tmp=1;
				point use=nod[j]-nod[i];
				
				//计算这条边在凸包上的概率 
				for (int k=0;k<n;++k) if (i!=k&&j!=k){
					if (use*(nod[k]-nod[i])>0) tmp*=(1-pr[k]);
					else if (use*(nod[k]-nod[i])>-1e-12&&dist(nod[i]-nod[k])<dist(nod[j]-nod[i]))
					tmp*=(1-pr[k]);
				}
				
				//累计答案 
				ans+=tmp*(nod[i]*nod[j])*pr[i]*pr[j];
			}
			
			//注意要除以2 ... 
			ans/=2;
			return fabs(ans);
		}
};
