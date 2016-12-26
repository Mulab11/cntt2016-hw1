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
#define mod 1000000007
int qpow(int a,int b,int p){
	int ret=1;
	for (;b;b>>=1,a=(ll)a*a%p) if (b&1) ret=(ll)ret*a%p;
	return ret;
}

/*
根据递推式求出通项式即可
*/

class TrafficCongestion{
public:
	int theMinCars(int tH){
		if (tH&1) return (ll)(qpow(2,tH+1,mod)-1)*qpow(3,mod-2,mod)%mod;
			else return (ll)(qpow(2,tH+1,mod)+1)*qpow(3,mod-2,mod)%mod;
	}
};
