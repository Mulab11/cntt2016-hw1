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
using namespace std;
const int maxn=55;
int dsr[maxn<<1],dc;
struct seg{int l,r;}a[maxn];
int n;

/*
每次抓鱼一定可以使得某条鱼抓到鱼头或鱼尾
暴力枚举即可
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
