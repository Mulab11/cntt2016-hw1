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
const int maxn=2505;
string s;
ll g[maxn][maxn];

/*
前面后面xjb O(n^2)DP一下
*/

class LittleElephantAndRGB{
public:
	ll getNumber(vector<string>lst,int mg){
		int n=lst.size();
		rep(i,0,n-1) s+=lst[i];
		n=s.size();
		ll ans=0;
		int cs=0,pos=n;
		drp(i,n-1,0){
			if (s[i]=='G') cs++;else cs=0;
			if (cs>=mg) pos=i;
			rep(j,1,mg){
				g[i][j]=g[i+1][j];
				if (cs>=j) g[i][j]+=n-i-j+1;
				else if (pos<n) g[i][j]+=n-pos-mg+1;
			}
		}
		rep(i,0,n-2){
			int mx=0,cs=0;
			rep(j,i,n-2){
				if (s[j]=='G') cs++,mx=max(mx,cs);
					else cs=0;
				if (mx>=mg) ans+=(n-1-j)*(n-j)/2;
					else ans+=g[j+1][mg-cs];
			}
		}
		return ans;
	}
};
