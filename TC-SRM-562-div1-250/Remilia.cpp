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
ll R,G,B;
vector<ll>ans;

/*
暴力一个
*/

struct PastingPaintingDivOne{
	vector<ll>countColors(vector<string>brd,int T){
		int n=brd.size(),m=brd[0].size();
		rep(y,0,m-1){
			int i=0,j=y,lst=-1;
			while (i<n&&j<m){
				if (brd[i][j]!='.'){
					int val=(lst==-1)?T:min(T,i-lst);
					if (brd[i][j]=='R') R+=val;
					if (brd[i][j]=='G') G+=val;
					if (brd[i][j]=='B') B+=val;
					lst=i;
				}
				i++,j++;
			}
		}
		rep(x,1,n-1){
			int i=x,j=0,lst=-1;
			while (i<n&&j<m){
				if (brd[i][j]!='.'){
					int val=(lst==-1)?T:min(T,i-lst);
					if (brd[i][j]=='R') R+=val;
					if (brd[i][j]=='G') G+=val;
					if (brd[i][j]=='B') B+=val;
					lst=i;
				}
				i++,j++;
			}
		}
		ans.pb(R),ans.pb(G),ans.pb(B);
		return ans;
	}
};
