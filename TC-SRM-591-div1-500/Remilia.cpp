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
using namespace std;
int gcd(int a,int b){return !b?a:gcd(b,a%b);}

/*
打表可以发现，这个就是下面这个公式
*/

class PyramidSequences{
public:
	ll distinctPairs(int n,int m){
		n--,m--;
		int g=gcd(n,m);
		ll ans=0;
		ans+=(ll)(n/g)*(m/g)*(g-1);
		ans+=(ll)(n/g+1)*(m/g+1)/2;
		return ans;
	} 
};
