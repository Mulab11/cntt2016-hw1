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

/*
ans=max(log)+sum(popcount)
*/

class IncrementAndDoubling{
public:
	int getMin(vector<int>a){
		int ans=0,cnt=0,n=a.size();
		rep(i,0,n-1) if (a[i]) cnt++;
		while (cnt){
			rep(i,0,n-1) if (a[i]&1){
				ans++;
				if (a[i]==1) cnt--;
			}
			if (!cnt) break;
			ans++;
			rep(i,0,n-1) a[i]>>=1;
		}
		return ans;
	}
};
