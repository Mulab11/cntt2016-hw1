#include<cstdio>
#include<vector>
//#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const double eps=1e-9;

struct point{
	int x,y;
	point (int a=0,int b=0):x(a),y(b){};
	inline point operator + (const point &a)const{
		return point(x+a.x,y+a.y);
	}
	inline point operator - (const point &a)const{
		return point(x-a.x,y-a.y);
	}
	inline long long operator * (const point &a)const{
		return (long long)x*a.y-(long long)y*a.x;
	}
};

class ConvexPolygonGame{
	private:
	
	int n,cnt;
	point nod[55];
	point rec[500000];
	
	bool insert(point a){
		if(cnt<2) rec[++cnt]=a;
		else{
			if ((a-rec[cnt])*(a-rec[cnt-1])) return false;
			rec[++cnt]=a;
			return true;
		}
	}
	
	inline int getn(double a){
		return (int)(a+1-eps);
	}
	
	inline void min(double &a,double b){
		if (a>b) a=b;
	}
	
	inline void max(double &a,double b){
		if (a<b) a=b;
	}
	
	public:
	
	string winner(vector<int> x,vector<int> y){
		n=x.size();
		for (int i=0;i<n;i++) nod[i]=point(x[i],y[i]);
		nod[n]=nod[0];
		for (int i=-100000;i<=100000;++i){
			double l=100000,r=-100000;
			for (int j=0;j<n;++j){
				if (nod[j].x==nod[j+1].x){
					if (nod[j].x==i){
						int a=nod[j].y,b=nod[j+1].y;
						if (a>b) swap(a,b);
						if (b-a>1){
							min(l,a+1);
							max(r,b-1);
						}
					}
				}
				else{
					if (nod[j].x==i||nod[j+1].x==i) continue;
					if ((long long)(i-nod[j].x)*(i-nod[j+1].x)<=0){
						double d=(nod[j+1].y-nod[j].y)/(double)(nod[j+1].x-nod[j].x)*(i-nod[j].x);
						min(l,d);
						max(r,d);
					}
				}
			}
			r+=eps;
			//printf("i=%d, l=%lf, r=%lf\n",i,l,r);
			for (int j=getn(l);j<=r;++j){
				if(!insert(point(i,j))) return "Masha";
			}
		}
		return "Petya";
	}
};