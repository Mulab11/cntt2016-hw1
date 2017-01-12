#include <bits/stdc++.h>

using namespace std;

struct orz{
	int x,y;
	orz(){}
	orz(int x,int y):x(x),y(y){}
	orz operator-(const orz&t){
		return orz(x-t.x,y-t.y);
	}
}a[55];
double p[55];

int cha(orz a,orz b){//叉积 
	return a.x*b.y-a.y*b.x;
}

class Constellation {
public:
	double expectation(vector <int> x, vector <int> y, vector <int> prob) {
		int n=x.size();
		for(int i=1;i<=n;++i)a[i]=orz(x[i-1],y[i-1]);
		for(int i=1;i<=n;++i)p[i]=prob[i-1]/1000.0;
		double ret=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)if(i!=j){//枚举一条有向边 
				double pr=p[i]*p[j];
				orz tmp=a[j]-a[i];
				int x1=a[i].x,x2=a[j].x,y1=a[i].y,y2=a[j].y;
				if(x1>x2)swap(x1,x2);
				if(y1>y2)swap(y1,y2);
				for(int k=1;k<=n;++k)if(i!=k&&j!=k){
					int t=cha(a[k]-a[i],tmp);
					if(t>0||(t==0&&x1<=a[k].x&&a[k].x<=x2&&y1<=a[k].y&&a[k].y<=y2))pr*=1-p[k];
					//不能在右侧或线段上 
				}
				ret+=pr*cha(a[i],a[j]);//贡献 
			}
		return ret/2;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
