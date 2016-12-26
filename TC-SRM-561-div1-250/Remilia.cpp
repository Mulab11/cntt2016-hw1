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

const int maxn=55;
vector<int>bal[2];
int upd(int &x,int y){
	if (x==-1||y<x) x=y;
}
struct ICPCBalloons{
	int minRepaintings(vector<int>bc,string bs,vector<int>ac){
		int n=bc.size(),s0=0,s1=0,m=ac.size();
		rep(i,0,n-1) if (bs[i]=='L') bal[1].pb(bc[i]),s1+=bc[i];
			else bal[0].pb(bc[i]),s0+=bc[i];
		sort(ac.begin(),ac.end());
		sort(bal[0].begin(),bal[0].end());
		sort(bal[1].begin(),bal[1].end());
		int ans=-1;
		// 枚举哪些用medium
		rep(i,0,(1<<m)-1){
			int z0=(int)bal[0].size()-1,z1=(int)bal[1].size()-1,n0=0,n1=0;
			rep(j,0,m-1) if ((i>>j)&1) n1+=ac[j];
				else n0+=ac[j];
			if (s0<n0||s1<n1) continue;
			int m0=0,m1=0;
			// 贪心，大的配大的
			drp(j,m-1,0){
				if ((i>>j)&1){
					if (z1>=0) m1+=min(ac[j],bal[1][z1]),z1--;
				}
				else if (z0>=0) m0+=min(ac[j],bal[0][z0]),z0--;
			}
			upd(ans,n0-m0+n1-m1);
		}
		return ans;
	}
};
