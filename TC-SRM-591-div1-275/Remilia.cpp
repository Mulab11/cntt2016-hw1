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
枚举直径较浅的一个端点，接着枚举lca，那么判合法就只要中间那一溜都是>1即可。
*/

class TheTree{
public:
	int maximumDiameter(vector<int>cnt){
		int n=cnt.size(),ans=0;
		rep(i,0,n-1){
			int ret=0;
			rep(j,i,n-1){
				if (cnt[j]==1){ret+=n-j;break;}
				ret+=2;
			}
			if (ret>ans) ans=ret;
		}
		return ans;
	}
};
