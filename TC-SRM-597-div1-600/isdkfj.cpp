#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

struct orz{//点 
	int x,y;
	orz(){}
	orz(int x,int y):x(x),y(y){}
	orz operator-(const orz&t){
		return orz(x-t.x,y-t.y);
	}
}a[55],p[200005];

struct gg{//线段 
	orz a,b;
	bool operator<(const gg&t)const{
		return a.x<t.a.x;
	}
}b[55];

LL cha(orz a,orz b){//叉积 
	return LL(a.x)*b.y-LL(a.y)*b.x;
}

set<pair<int,int> >s;

int ss(LL s,int t){//取上整 
	int sgn=0;
	if(s<0)sgn^=1;
	if(t<0)sgn^=1;
	s=abs(s);t=abs(t);
	t=s/t;
	if(sgn)return -t;
	return t+1;
}

int xx(LL s,int t){//取下整 
	int sgn=0;
	if(s<0)sgn^=1;
	if(t<0)sgn^=1;
	s=abs(s);t=abs(t);
	t=s/t;
	if(sgn)return -t-1;
	return t;
}

class ConvexPolygonGame {
public:
	string winner(vector <int> X, vector <int> Y) {
		int n=X.size(),cnt=0,mn=1000000,mx=-1000000;
		for(int i=0;i<n;++i){
			b[i].a=orz(X[i],Y[i]);
			b[i].b=orz(X[(i+1)%n],Y[(i+1)%n]);
			if(b[i].a.x>b[i].b.x)swap(b[i].a,b[i].b);
			s.insert(make_pair(X[i],Y[i]));
			mn=min(mn,X[i]);
			mx=max(mx,X[i]);
		}
		sort(b,b+n);
		for(int x=mn;x<=mx;++x){//扫描线 
			int y1=992844353,y2=-998244353;
			for(int j=0;j<n;++j)
			if(b[j].a.x<=x&&b[j].b.x>=x){
				if(b[j].a.x==b[j].b.x){
					y1=min(y1,max(b[j].a.y,b[j].b.y));
					y2=max(y2,min(b[j].a.y,b[j].b.y));
				}else {
					LL l=LL(b[j].b.y-b[j].a.y)*x+LL(b[j].a.y)*b[j].b.x-LL(b[j].b.y)*b[j].a.x;
					int r=b[j].b.x-b[j].a.x,t=l/r;
					if(l%r==0){
						y1=min(y1,t);y2=max(y2,t);
					}else {
						y1=min(y1,ss(l,r));y2=max(y2,xx(l,r));
					}
				}//求出最大的y和最小的y 
			}
			for(int y=y1;y<=y2;++y){
				if(s.find(make_pair(x,y))!=s.end())continue;//在原来的凸包上 
				p[++cnt]=orz(x,y);
				if(cnt>200001)return "Masha";//超过这么多一定存在 
			}
		}
		if(cnt<3)return "Petya";//不足三个 
		orz tmp=p[2]-p[1];
		for(int i=3;i<=cnt;++i)
		if(cha(p[i]-p[1],tmp))return "Masha";//不共线 
		return "Petya";
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
