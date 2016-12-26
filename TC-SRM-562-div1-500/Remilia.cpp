#include<bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
#define VS vector<string>
#define MC(a,b) memcpy(a,b,sizeof b)
#define MS(a,b) memset(a,b,sizeof a)

using namespace std;

const int maxn=230;
struct point{
	int x,y;
	point(int X=0,int Y=0){x=X,y=Y;}
}w[maxn],b[maxn];
point operator -(const point&a,const point&b){return point(a.x-b.x,a.y-b.y);}
int n,m;
string s;

bitset<maxn>c[maxn][maxn*2],tmp,all;

ll chaji(point a,point b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}
struct CheckerFreeness{
	string isFree(VS wx,VS wy,VS bx,VS by){
		rep(i,0,wx.size()-1) s+=wx[i];
		rep(nw,0,s.size()-1){
			int tmp=0;
			while (nw<s.size()&&isdigit(s[nw])) tmp=tmp*10+s[nw++]-'0';
			w[++n].x=tmp;
		}
		n=0;s.clear();rep(i,0,wy.size()-1) s+=wy[i];
		rep(nw,0,s.size()-1){
			int tmp=0;
			while (nw<s.size()&&isdigit(s[nw])) tmp=tmp*10+s[nw++]-'0';
			w[++n].y=tmp;
		}
		s.clear();rep(i,0,bx.size()-1) s+=bx[i];
		rep(nw,0,s.size()-1){
			int tmp=0;
			while (nw<s.size()&&isdigit(s[nw])) tmp=tmp*10+s[nw++]-'0';
			b[++m].x=tmp;
		}
		m=0;s.clear();rep(i,0,by.size()-1) s+=by[i];
		rep(nw,0,s.size()-1){
			int tmp=0;
			while (nw<s.size()&&isdigit(s[nw])) tmp=tmp*10+s[nw++]-'0';
			b[++m].y=tmp;
		}
		// xjb预处理半平面内的点数
		rep(i,1,n){
			rep(j,1,n) if (i!=j) rep(k,1,m)
				if (chaji(w[i]-b[k],w[j]-b[k])>0) c[i][j][k]=1;else c[i][j][k]=0;
			rep(j,1,m) rep(k,1,m) if (j!=k)
				if (chaji(w[i]-b[k],b[j]-b[k])>0) c[i][n+j][k]=1;else c[i][n+j][k]=0;
		}
		rep(i,1,m) all[i]=1;
		// 枚举一下然后求个交count点数
		rep(i,1,n) rep(j,i+1,n) rep(k,1,m){
			if (c[i][j][k]) tmp=c[i][j]^all;else tmp=c[i][j]&all;
			tmp&=c[i][n+k]^c[j][n+k];
			if (tmp.count()) return "NO";
		} 
		return "YES";
	}
};
