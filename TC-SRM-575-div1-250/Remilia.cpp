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

/*
充要条件是n为奇数或2的奇数次幂
*/

struct TheNumberGameDivOne{
	string find(ll n){
		if (n&1) return "Brus";
		int lg=0;
		for (;!(n&1);n>>=1,lg++);
		if (n==1&&(lg&1)) return "Brus";
		return "John";
	}
};
