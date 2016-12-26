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
bool f[maxn*20000];

/*
答案只和某一部分的a+b有关，背包即可
*/

class MayTheBestPetWin{
public:
	int calc(vector<int>a,vector<int>b){
		int n=a.size(),ta=0,tb=0;
		rep(i,0,n-1) ta+=a[i],tb+=b[i];
		f[0]=1;
		rep(i,0,n-1){
			int v=a[i]+b[i];
			drp(j,(i+1)*20000,v) if (f[j-v]) f[j]=1;
		}
		int ans=tb;
		rep(i,0,n*20000) if (f[i]) ans=min(ans,max(i-ta,tb-i));
		return ans;
	}
};
