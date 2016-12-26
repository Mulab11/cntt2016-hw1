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
#define VI vector<int>
#define VS vector<string>
#define MC(a,b) memcpy(a,b,sizeof b)
#define MS(a,b) memset(a,b,sizeof a)

using namespace std;

const int maxx=600;
int n,dist[maxx][maxx],ex[maxx][maxx];
bool cmp(int x,int y){
	return (~x)&&x<=y;
}
int pre[maxx][maxx];
// 矩阵和
int mat(int x1,int x2,int y1,int y2){
	int ret=pre[x2][y2];
	if (x1) ret-=pre[x1-1][y2];
	if (y1) ret-=pre[x2][y1-1];
	if (x1&&y1) ret+=pre[x1-1][y1-1];
	return ret;
}
// 二维前缀和
bool check(int x){
	rep(i,0,560) rep(j,0,560){
		if ((!((i^x)&1))&&(!((j^x)&1))&&dist[i][j]<=x) pre[i][j]=1;else pre[i][j]=0;
		if (i) pre[i][j]+=pre[i-1][j];
		if (j) pre[i][j]+=pre[i][j-1];
		if (i&&j) pre[i][j]-=pre[i-1][j-1];
	}
	rep(j,x,560-x) rep(k,x,560-x)
		if (!ex[j][k]&&mat(j-x,j+x,k-x,k+x)==(x+1)*(x+1)) return 0;
	return 1;
}
void upd(int &x,int y){
	if (x==-1||y<x) x=y;
}
struct DrawingPointsDivOne{
	int maxSteps(VI x,VI y){
		n=x.size();
		rep(i,0,n-1) (x[i]<<=1)+=280,(y[i]<<=1)+=280;
		memset(dist,-1,sizeof dist);
		rep(i,0,n-1) ex[x[i]][y[i]]=1;
		// 判断每个点是否存在
		rep(i,0,n-1) rep(j,0,560) rep(k,0,560)
			if (!((abs(x[i]-j)+abs(y[i]-k))&1)) upd(dist[j][k],max(abs(x[i]-j),abs(y[i]-k)));
		// 二分答案
		int l=0,r=139;
		while (l<r){
			int mid=l+r+1>>1;
			if (check(mid)) l=mid;else r=mid-1;
		}
		if (l==139&&check(l)) return -1;
			else return l; 
	}
};
