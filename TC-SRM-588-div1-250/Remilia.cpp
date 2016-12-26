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
vector<int>a;
bool cmp(const int&x,const int&y){
	return a[x]<a[y];
}
int b[maxn],id[maxn];

/*
排序，DP
dp[i][j]表示最后一首歌是i，已经唱了j首的最短时间。
xjb转移即可。
*/

class GUMIAndSongsDiv1{
public:
	int maxSongs(vector<int>dur,vector<int>ton,int T){
		a=ton;
		int n=dur.size();
		rep(i,0,n-1) id[i]=i;
		sort(id,id+n,cmp);
		int ans=0;
		rep(i,0,n-1) rep(j,i,n-1){
			rep(k,i,j) b[k-i]=dur[id[k]];
			sort(b,b+j-i+1);
			int nw=ton[id[j]]-ton[id[i]],cnt=0;
			for (int k=0;k<=j-i&&nw+b[k]<=T;k++) cnt++,nw+=b[k];
			ans=max(ans,cnt);
		}
		return ans;
	}
};
