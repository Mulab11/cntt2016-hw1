#include <bits/stdc++.h>

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
using namespace std;
#define y1 fkjsaklfjaskldf
#define y2 fkasjfklasfdasfasdkjf
const int maxl=200005;
PII seg[maxl];
double findsj(int x1,int y1,int x2,int y2,int x){
	if (x1==x2) return max(y1,y2);
	double k=1.0*(y2-y1)/(x2-x1);
	return y1+(x-x1)*k;
}
double findxj(int x1,int y1,int x2,int y2,int x){
	if (x1==x2) return min(y1,y2);
	double k=1.0*(y2-y1)/(x2-x1);
	return y1+(x-x1)*k;
}

/*

好搞笑啊这个题。。。居然是个600。。。

*/

class ConvexPolygonGame{
public:
	string winner(vector<int>x,vector<int>y){
		int n=x.size(),mx=0;
		rep(i,0,n-1) if (x[i]<x[mx]||(x[i]==x[mx]&&y[i]<y[mx])) mx=i;
		int up1=mx,up2=(mx+n-1)%n,down1=mx,down2=(mx+1)%n,now=x[mx];
		while (up1!=down2){
			while (now<=x[up2]&&now<=x[down2]){
				int sj=floor(findsj(x[up1],y[up1],x[up2],y[up2],now)),xj=ceil(findxj(x[down1],y[down1],x[down2],y[down2],now));
				if (now==x[up1]||now==x[up2]) sj--;
				if (now==x[down1]||now==x[down2]) xj++;
				seg[now-x[mx]]=mk(xj,sj);now++;
			}
			if (now>x[up2]) up1=(up1+n-1)%n,up2=(up2+n-1)%n;
			if (up1==down2) break;
			if (now>x[down2]) down1=(down1+1)%n,down2=(down2+1)%n;
		}
		int nd=0,x1,y1,x2,y2;
		rep(i,0,now-x[mx]-1){
			if (seg[i].sc<seg[i].fs) continue;
			if (seg[i].sc==seg[i].fs){
				if (!nd) nd++,x1=i,y1=seg[i].fs;
				else if (nd==1){
					nd++;
					x2=i,y2=seg[i].fs;
				}
				else if ((ll)(i-x1)*(seg[i].fs-y2)!=(ll)(i-x2)*(seg[i].fs-y1)) return "Masha";
			}
			else if (!nd) nd+=2,x1=x2=i,y1=seg[i].fs,y2=seg[i].sc;else return "Masha";
		}
		return "Petya";
	}
};
