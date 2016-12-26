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

/*
Ah...
每个质因子的最大次数+质因子个数。。。
*/

int lg(ll a){
	int ret=0;
	ll nw=1;
	while (nw<a) ret++,nw<<=1;
	return ret; 
}
class BigFatInteger{
public:
	int minOperations(int A,int B){
		int ans=0,mx=0;
		for (int i=2;i*i<=A;i++){
			if (A%i==0){
				int cnt=0;
				ans++;
				while (A%i==0) A/=i,cnt++;
				mx=max(mx,cnt); 
			}
		}
		if (A>1) ans++,mx=max(mx,1);
		return ans+lg((ll)mx*B);
	}
};
