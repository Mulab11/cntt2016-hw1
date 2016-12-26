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

const int maxn=55;
int num[maxn][2];

/*
每一位是独立的
分开考虑取max即可
*/

struct TheDevice{
	int minimumAdditional(vector<string>plt){
		int n=plt.size(),m=plt[0].size();
		rep(i,0,n-1) rep(j,0,m-1) num[j][plt[i][j]-'0']++;
		int ans=0;
		rep(j,0,m-1){
			if (num[j][0]==0) ans=max(ans,max(2-num[j][1],0)+1);
			else ans=max(ans,max(2-num[j][1],0));
		}
		return ans;
	}
};
