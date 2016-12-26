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
const int maxn=2505;
int dist[55][55],vis[55][55];
int head,tail;
PII que[maxn*maxn];
void upd(int x,int y,int d){
	if (d<dist[x][y]){
		dist[x][y]=d;
		if (!vis[x][y]){
			que[(++tail)%maxn]=mk(x,y);
			vis[x][y]=1;
		}
	}
}
int n,m;

/*
xjb连个边求最小瓶颈路
*/

struct ArcadeManao{
	int shortestLadder(vector<string>mp,int cn,int cm){
		n=mp.size(),m=mp[0].size();
		memset(dist,30,sizeof dist);
		dist[n-1][0]=0;
		head=1,tail=0;que[++tail]=mk(n-1,0);
		while (head<=tail){
			int nx=que[head%maxn].fs,ny=que[head%maxn].sc;
			head++,vis[nx][ny]=0;
			drp(j,ny-1,0){
				if (mp[nx][j]!='X') break;
				upd(nx,j,dist[nx][ny]);
			}
			rep(j,ny+1,m-1){
				if (mp[nx][j]!='X') break;
				upd(nx,j,dist[nx][ny]);
			}
			rep(i,nx+1,n-1) if (mp[i][ny]=='X') upd(i,ny,max(dist[nx][ny],i-nx));
			drp(i,nx-1,0) if (mp[i][ny]=='X') upd(i,ny,max(dist[nx][ny],nx-i));
		}
		return dist[cn-1][cm-1];
	}
};
