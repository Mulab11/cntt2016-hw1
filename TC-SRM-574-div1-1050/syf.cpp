//============================================================================
// Author       : Sun YaoFeng
//============================================================================

//#pragma 	comment(linker, "/STACK:100240000,100240000")
//#include	<cstdio>
//#include	<cstdlib>
//#include	<cstring>
//#include	<algorithm>

#include	<bits/stdc++.h>

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

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

char s[N][N];
int col[N][N],deg[N][N],mn[N*N],mx[N*N];
int LU[N],LD[N],RU[N],RD[N],LR[N];
int n,m,num;

void Upmax(int &x,int y) {x=max(x,y);}
void Upmin(int &x,int y) {x=min(x,y);}
void dfs(int x,int y){	//暴搜连通块
	if (x<1||x>n||y<1||y>m||col[x][y]||s[x][y]!='X') return;
	col[x][y]=num;
	Upmin(mn[num],x);
	Upmax(mx[num],x);
	For(i,0,4) dfs(x+dx[i],y+dy[i]);
}
int dp(){	//DP计算出最小值
	static int f[N][N][N];
	memset(f,200,sizeof(f));
	f[0][0][0]=0;
	
	//f[i][j][k] 表示前i行，有j个左括号，k个右括号的答案
	
	For(i,0,n){
		For(x,0,i+1) For(y,0,i+1)
			if (f[i][x][y]>=0){
				for (int a=-1;a<=1;a++)
					for (int b=-1;b<=1;b++){
						if (a==1&&!LD[i+1]) continue;
						if (a==-1&&!LU[i+1]) continue;
						if (b==1&&!RD[i+1]) continue;
						if (b==-1&&!RU[i+1]) continue;
						if (a==b&&a&&LR[i+1]) continue;
						if (x+a>=0&&y+b>=0){
							Upmax(f[i+1][x+a][y+b],f[i][x][y]+(a==-1)+(b==-1));
						}
					}
			}
	}
	return f[n][0][0];
}

class Tunnels{
public:
	int minimumTunnels(Vs frame){
		memset(mn,60,sizeof(mn));
		memset(mx,0,sizeof(mx));
		n=frame.size();
		m=frame[0].length();
		For(i,1,n+1)
			For(j,1,m+1){
				s[i][j]=frame[i-1][j-1];
			}
		For(i,1,n+1)
			For(j,1,m+1){
				if (!col[i][j]&&s[i][j]=='X') num++,dfs(i,j);
				For(k,0,4) if (s[i+dx[k]][j+dy[k]]=='X') deg[i][j]++;
			}
		
		//预处理每一个连通块的信息
			
		if (m==1) return num>0;
		For(i,1,n+1){
			if (s[i][1]=='X'&&deg[i][1]<=1){
				if (i==mn[col[i][1]]) LU[i]=1;
				if (i==mx[col[i][1]]) LD[i]=1;
			}
			if (s[i][m]=='X'&&deg[i][m]<=1){
				if (i==mn[col[i][m]]) RU[i]=1;
				if (i==mx[col[i][m]]) RD[i]=1;
			}
			if (col[i][1]==col[i][m]&&col[i][1]) LR[i]=1;
		}
		
		//确定每一个连通块是哪一种类型，诸如左括号、右括号等等
		
		For(i,3,n+1){
			if (LU[i-1]) LD[i]=0;
			if (RU[i-1]) RD[i]=0;
		}
		For(i,2,n+1){
			int cl=col[i][1],cr=col[i][m];
			if (cl!=cr){
				if (cl&&mn[cl]==mx[cl]) LD[i]=0;
				if (cr&&mn[cr]==mx[cr]) RD[i]=0;
			}
		}
		return num-dp();
	}
} T;