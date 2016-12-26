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

/*
执行4次之后的朝向总是相同的，位移当然也是相同的。暴力模拟即可。
*/

int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int nx,ny,nd;
struct RobotHerb{
	ll getdist(int T,vector<int>a){
		int n=a.size();
		rep(i,0,n-1){
			nx+=dir[nd][0]*a[i],ny+=dir[nd][1]*a[i];
			nd=(nd+a[i])%4;
		}
		if (!nd) return (ll)T*(abs(nx)+abs(ny));
		else{
			T%=4;
			if (!T) return 0;
			while (--T){
				rep(i,0,n-1){
					nx+=dir[nd][0]*a[i],ny+=dir[nd][1]*a[i];
					nd=(nd+a[i])%4;
				}
			}
			return abs(nx)+abs(ny);
		}
	}
};
