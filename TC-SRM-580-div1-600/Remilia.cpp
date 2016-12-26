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
using namespace std;
const int maxn=55;
int dsr[maxn<<1],dc;
struct seg{int l,r;}a[maxn];
int n;

/*
枚举起点
然后就只要求出右端点大于当前左端点的线段中，左端点最小的；左端点小于当前右端点的线段中，右端点最大的即可。
暴力模拟O(n^2)
*/

class EelAndRabbit{
public:
	int getmax(vector<int>len,vector<int>t){
		n=len.size();
		rep(i,0,n-1){
			a[i].l=-t[i]-len[i],a[i].r=-t[i];
			dsr[++dc]=-t[i]-len[i],dsr[++dc]=-t[i];
		}
		sort(dsr+1,dsr+dc+1);
		dc=unique(dsr+1,dsr+dc+1)-dsr-1;
		rep(i,0,n-1){
			a[i].l=lower_bound(dsr+1,dsr+dc+1,a[i].l)-dsr;
			a[i].r=lower_bound(dsr+1,dsr+dc+1,a[i].r)-dsr;
		}
		int ans=0;
		rep(i,1,dc) rep(j,i,dc){
			int ret=0;
			rep(k,0,n-1) if ((i<=a[k].r&&i>=a[k].l)||(j<=a[k].r&&j>=a[k].l)) ret++;
			ans=max(ans,ret);
		}
		return ans;
	}
};
