//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>

#define For(i,x,y) for (int i=x;i<y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;
typedef vector<string> Vs;

const int N=50+19;

Vs s;
int col[N][N];
int b,n,m;

int dfs(int x,int y,int c){	//用二分图判断
	if (x<0||x>=n||y<0||y>=m||s[x][y]!='X') return 1;
	if (~col[x][y]){
		return col[x][y]==c;
	} else{
		col[x][y]=c;
	}
	if (!dfs(x-1,y,c^1)) return 0;
	if (!dfs(x-1,y+1,c^1)) return 0;
	if (!dfs(x,y-1,c^1)) return 0;
	if (!dfs(x,y+1,c^1)) return 0;
	if (!dfs(x+1,y,c^1)) return 0;
	if (!dfs(x+1,y-1,c^1)) return 0;
	return 1;
}

class HexagonalBoard{
public:
	int minColors(Vs s){	//判断答案是否是1或者2，否则输出3
		::s=s;
		n=s.size();
		m=s[0].length();
		b=1;
		For(i,0,n) For(j,0,m){
			if (s[i][j]=='X') b=0;
		}
		if (b) return 0;
		b=1;
		For(i,0,n) For(j,0,m)
			if (s[i][j]=='X'){
				if (j+1<m&&s[i][j+1]=='X') b=0;
				if (i+1<n&&s[i+1][j]=='X') b=0;
				if (i+1<n&&j>0&&s[i+1][j-1]=='X') b=0;
			}
		if (b) return 1;
		memset(col,-1,sizeof(col));
		For(i,0,n) For(j,0,m)
			if (s[i][j]=='X'&&col[i][j]==-1){
				if (!dfs(i,j,0)) return 3;
			}
		return 2;
	}
} T;