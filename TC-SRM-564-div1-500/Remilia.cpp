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

/*
分为若干部分：
rgb
rgrgrg/rbrbrb
rrr
特判计算即可O(1)
*/

struct AlternateColors2{
	ll countWays(int n,int k){
		ll ans=0;
		if (k%3==1){
			int rem=n-(k/3+1)*3;
			if (rem>=0) ans+=1ll*(rem+2)*(rem+1)/2;
		}
		rep(i,0,(k-1)/3) if ((k-i*3)&1){
			int rem=n-k-1;
			ans+=2*(rem+1);
		}
		rep(i,1,k){
			int z=i-1,xx=0,sx=z/3;
			if (z&1) xx++;
			if ((z-sx*3)&1) sx--;
			if (sx>=xx) ans+=((sx-xx)/2+1)*2;
			if (sx*3==z) ans--;
		}
		return ans;
	}
};
