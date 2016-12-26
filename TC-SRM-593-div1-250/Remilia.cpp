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
const int dir[6][2]={{-1,1},{-1,0},{0,-1},{1,-1},{1,0},{0,1}};
#define x2 fjasklfjaklsdf
#define y2 fklasjfskldjfsad
int ex[3],n,m,col[55][55];
vector<string>S;
bool dfs(int x,int y){
	rep(i,1,2) ex[i]=0;
	rep(i,0,5){
		int _x=x+dir[i][0],_y=y+dir[i][1];
		if (_x>=0&&_x<n&&_y>=0&&_y<m&&S[_x][_y]=='X'&&col[_x][_y]) ex[col[_x][_y]]=1;
	}
	if (ex[1]&&ex[2]) return 0;
	if (!ex[1]) col[x][y]=1;else col[x][y]=2;
	rep(i,0,5){
		int _x=x+dir[i][0],_y=y+dir[i][1];
		if (_x>=0&&_x<n&&_y>=0&&_y<m&&S[_x][_y]=='X'&&!col[_x][_y]){
			if (!dfs(_x,_y)) return 0;
		}
	}
	return 1;
}

/*
ans<=3
=2  ->二分图
=1  ->连通块大小=1
*/

class HexagonalBoard{
public:
	int minColors(vector<string>s){
		n=s.size(),m=s[0].size();S=s;
		rep(i,0,n-1) rep(j,0,m-1){
			if (s[i][j]=='X'&&!col[i][j]){
				if (!dfs(i,j)) return 3;
			}
		}
		rep(i,0,n-1) rep(j,0,m-1){
			if (s[i][j]=='-') continue;
			rep(k,0,5){
				int x=i+dir[k][0],y=j+dir[k][1];
				if (x>=0&&x<n&&y>=0&&y<m&&s[x][y]=='X') return 2;
			}
		}
		rep(i,0,n-1) rep(j,0,m-1) if (s[i][j]=='X') return 1;
		return 0;
	}
};
