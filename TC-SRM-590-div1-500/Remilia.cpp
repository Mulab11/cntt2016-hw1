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
const int maxn=55;
ll bas[maxn];
int n,bc,zyy;
ll ans=1;
ll qpow(ll a,ll b){
	ll ret=1;
	for (;b;b>>=1,a=a*a) if (b&1) ret=ret*a;
	return ret;
}
ll nw=0;

/*
我说xjb线性基消一发逐位确定你兹磁不兹磁啊。。？
*/
class XorCards{
public:
	ll numberOfWays(vector<ll>a,ll limit){
		n=a.size();
		rep(i,0,n-1){
			if (!a[i]){zyy++;continue;}
			drp(j,49,0) if ((a[i]>>j)&1){
				if (!bas[j]){bas[j]=a[i];break;}
				else a[i]^=bas[j];
				if (!a[i]){zyy++;break;}
			}
		}
		drp(i,48,0) rep(j,i+1,49) if ((bas[j]>>i)&1) bas[j]^=bas[i];
		rep(i,0,49) if (bas[i]) bas[bc++]=bas[i];
		drp(i,bc-1,0){
			ll mx=max(nw,nw^bas[i]),mn=min(nw,nw^bas[i]);
			if (mx<=limit) ans+=qpow(2,i),nw=mx;
				else nw=mn;
		}
		return ans*qpow(2,zyy);
	}
};
