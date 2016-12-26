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
直接走上去如果wei掉就不要走第一步。
*/

class JumpFurther{
public:
	int furthest(int n,int badstep){
		int ans=0;
		rep(i,1,n){
			if (ans+i!=badstep) ans+=i;
				else ans+=i-1;
		}
		return ans;
	}
};
