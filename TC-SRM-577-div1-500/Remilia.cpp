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
const int maxn=70;
struct blc{
	int x,y;
	blc(int X=0,int Y=0){x=X,y=Y;}
}a[maxn];
int ans=0,n;
int f[15][15][15][15],pre[15][15],s[15][15];
int mat(int x1,int y1,int x2,int y2){
	int ret=pre[x2][y2];
	if (x1) ret-=pre[x1-1][y2];
	if (y1) ret-=pre[x2][y1-1];
	if (x1&&y1) ret+=pre[x1-1][y1-1];
	return ret;
}
int vis[maxn],tim;
void upd(int &x,int y){
	if (x==-1||y<x) x=y;
}

/*

记一下四个方向上的边界，然后dp即可。

*/

class EllysChessboard{
public:
	int minCost(vector<string>bod){
		rep(i,0,7) rep(j,0,7) if (bod[i][j]=='#') a[++n]=blc(i+j,i-j+7);
		if (!n) return 0;
		memset(f,-1,sizeof f);
		rep(i,1,n) f[a[i].x][a[i].x][a[i].y][a[i].y]=0;
		rep(i,1,n) pre[a[i].x][a[i].y]=1,s[a[i].x][a[i].y]=i;
		rep(i,1,14) pre[i][0]+=pre[i-1][0],pre[0][i]+=pre[0][i-1]; 
		rep(i,1,14) rep(j,1,14) pre[i][j]+=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
		rep(lx,0,14) rep(xa,0,14-lx) rep(ly,0,14) rep(ya,0,14-ly){
			int xb=xa+lx,yb=ya+ly;
			if (f[xa][xb][ya][yb]==-1) continue;
			int v=f[xa][xb][ya][yb];
			++tim;
			rep(i,1,n){
				if (vis[i]==tim) continue;
				int x=a[i].x,y=a[i].y;
				if (x<xa){
					if (y<ya){
						if (mat(x,y,xb,ya-1)+mat(x,ya,xa-1,yb)==1) upd(f[x][xb][y][yb],v+max(xb-x,yb-y));
					}
					else if (y<=yb){
						if (!mat(x+1,ya,xa-1,yb)){
							int add=0;
							rep(i,ya,yb) if (s[x][i]) add+=max(xb-x,max(yb-i,i-ya)),vis[s[x][i]]=tim;
							upd(f[x][xb][ya][yb],v+add);
						}
					}
					else{
						if (mat(x,ya,xa-1,y)+mat(xa,yb+1,xb,y)==1) upd(f[x][xb][ya][y],v+max(xb-x,y-ya));
					}
				}
				else if (x<=xb){
					if (y<ya){
						if (!mat(xa,y+1,xb,ya-1)){
							int add=0;
							rep(i,xa,xb) if (s[i][y]) add+=max(yb-y,max(xb-i,i-xa)),vis[s[i][y]]=tim;
							upd(f[xa][xb][y][yb],v+add);
						}
					}
					else if (y>yb){
						if (!mat(xa,yb+1,xb,y-1)){
							int add=0;
							rep(i,xa,xb) if (s[i][y]) add+=max(y-ya,max(xb-i,i-xa)),vis[s[i][y]]=tim;
							upd(f[xa][xb][ya][y],v+add);
						}
					}
				}
				else{
					if (y<ya){
						if (mat(xa,y,x,ya-1)+mat(xb+1,ya,x,yb)==1) upd(f[xa][x][y][yb],v+max(x-xa,yb-y));
					}
					else if (y<=yb){
						if (!mat(xb+1,ya,x-1,yb)){
							int add=0;
							rep(i,ya,yb) if (s[x][i]) add+=max(x-xa,max(yb-i,i-ya)),vis[s[x][i]]=tim;
							upd(f[xa][x][ya][yb],v+add);
						}
					}
					else{
						if (mat(xa,yb+1,x,y)+mat(xb+1,ya,x,yb)==1) upd(f[xa][x][ya][y],v+max(x-xa,y-ya));
					}
				}
			}
		}
		int lx=14,rx=0,ly=14,ry=0;
		rep(i,1,n) lx=min(lx,a[i].x),rx=max(rx,a[i].x),ly=min(ly,a[i].y),ry=max(ry,a[i].y);
		return f[lx][rx][ly][ry];
	}
};