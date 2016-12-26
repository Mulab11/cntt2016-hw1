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
int dist[maxn][maxn],n;
void upd(int &x,int y){
	if (x==-1||x>y) x=y;
}
/*
差分约束模型，枚举起点求最长的最短路即可。
*/
class Egalitarianism{
public:
	int maxDifference(vector<string>mp,int d){
		memset(dist,-1,sizeof dist);
		n=mp.size();
		rep(i,0,n-1) dist[i][i]=0;
		rep(i,0,n-1) rep(j,0,n-1) if (mp[i][j]=='Y') dist[i][j]=d;
		rep(k,0,n-1) rep(i,0,n-1) if (~dist[i][k])
			rep(j,0,n-1) if (~dist[k][j]) upd(dist[i][j],dist[i][k]+dist[k][j]);
		rep(i,0,n-1) rep(j,0,n-1) if (dist[i][j]==-1) return -1;
		int ans=0;
		rep(i,0,n-1) rep(j,0,n-1) ans=max(ans,dist[i][j]);
		return ans;
	}
};
