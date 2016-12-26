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

一层一层做，每层是奇数偶数交点求个和，乘个三角函数，因为高都是一样的，可以一起算。

*/

class TriangleXor{
public:
	int theArea(int m){
		double ans=0;
		if (!(m&1)) ans+=m/4.0;
		double lh=0,nh=0,di;
		rep(i,1,m){
			nh=1.0*i/(m+i);
			if (i&1) di=m-2*m*nh,ans+=(nh-lh)*m;
			ans+=di*(nh-lh)/2;
			lh=nh;
		}
		return (int)ans;
	}
};
