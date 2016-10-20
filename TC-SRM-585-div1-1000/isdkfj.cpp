#include <bits/stdc++.h>

using namespace std;

int m,sz;
void nxt(int&x,int&y){//求逆时针方向的下一个点 
	if(y==0&&x<m)++x;else if(x==m&&y<m)++y;
	else if(y==m&&x>0)--x;else if(x==0&&y>0)--y;
}
struct orz{int x,y;}p[22];
typedef long long LL;
LL cha(int x1,int y1,int x2,int y2){return LL(x1)*y2-LL(x2)*y1;}//叉积 
bool chk(int x1,int y1,int x2,int y2){//判断是否所有点都在该向量左侧 
	x2-=x1,y2-=y1;
	for(int i=1;i<=sz;++i)
	if(cha(x2,y2,p[i].x-x1,p[i].y-y1)<0)return 0;
	return 1;
}
int f[500005],g[500005];
LL su[500005];

class EnclosingTriangle {
public:
	long long getNumber(int m, vector <int> x, vector <int> y) {
		::m=m;
		sz=x.size();
		for(int i=1;i<=sz;++i)p[i].x=x[i-1],p[i].y=y[i-1];
		int n=4*m,bx,by,cx,cy,t1,t2,xx,yy;
		t1=m+1;bx=m;by=0;
		while(t1<n){xx=bx;yy=by;nxt(xx,yy);
			if(chk(0,0,xx,yy))bx=xx,by=yy,++t1;else break;}
		t2=t1,cx=bx,cy=by;
		while(t2<=n){if(chk(cx,cy,0,0))break;
			++t2;nxt(cx,cy);}
		f[1]=t1;g[1]=t2;su[1]=t1;//求f[1]和g[1] 
		for(int i=2,j=0,k=0;i<n;++i){
			nxt(j,k);
			while(t1<n){xx=bx;yy=by;nxt(xx,yy);
				if(chk(j,k,xx,yy))bx=xx,by=yy,++t1;else break;}
			f[i]=t1;su[i]=su[i-1]+f[i];//利用单调性求f[i]并维护前缀和 
			while(t2<=n){if(chk(cx,cy,j,k))break;
				++t2;nxt(cx,cy);}
			g[i]=t2;//利用单调性求g[i] 
		}
		LL ans=0;
		for(int a=1,t=1,l,r;a<n;++a){
			if(g[a]>n)break;
			while(t<=n&&f[t]<=g[a]-1)++t;//利用单调性求最小的t满足f[t]>g[a]-1 
			if(t>n)break;
			l=a+1,r=f[a]-1;
			if(l<=r&&t<=r){
				l=max(t,l);
				ans+=su[r]-su[l-1]+r-l+1-LL(g[a])*(r-l+1);
				//计算sigma(max(f[b]-g[a]+1,0)) 
			}
			ans+=max(f[f[a]]-max(g[a],f[a]+1)+1,0);//对于b=f[a]单独讨论 
		}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
