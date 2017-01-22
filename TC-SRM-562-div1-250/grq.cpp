#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

int n,m;
char col[205][205];

inline void copy(int x,vector<string> b){
	for(int i=x;i<x+n;i++)
		for(int j=x;j<x+m;j++){
			if(b[i-x][j-x]=='.') continue;
			col[i][j]=b[i-x][j-x];
		}
}
vector<ll> calc(){
	vector<ll> ans;ans.clear();
	for(int i=0;i<3;i++) ans.pb(0);
	for(int i=1;i<=200;i++) for(int j=1;j<=200;j++)
		if(col[i][j]=='R') ans[0]++; else if(col[i][j]=='G') ans[1]++; else if(col[i][j]=='B') ans[2]++;
	return ans;
}

class PastingPaintingDivOne{
public:
	vector<long long> countColors(vector<string> clipboard, int T){
		n=clipboard.size();m=clipboard[0].size();
		for(int i=1;i<=200;i++)for(int j=1;j<=200;j++) col[i][j]='.';
		vector<ll> ans,tmp;
		for(int i=1;i<=n&&i<=m;i++){
			copy(i,clipboard);
			if(T==i) return calc();
		}
		ans=calc();
		copy(min(n,m)+1,clipboard);
		tmp=calc();
		for(int i=0;i<3;i++) ans[i]+=(ll)(T-min(n,m))*(tmp[i]-ans[i]);
		return ans;
	}
};
