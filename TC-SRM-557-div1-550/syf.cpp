//============================================================================
// Author       : Sun YaoFeng
//============================================================================

//#pragma 	comment(linker, "/STACK:100240000,100240000")
//#include	<cstdio>
//#include	<cstdlib>
//#include	<cstring>
//#include	<algorithm>

#include	<bits/stdc++.h>

using	namespace	std;

#define DB		double
#define	lf		else if
#define I64		long long
#define	Rd()	(rand()<<15|rand())
#define For(i,a,b)	for(int i=a,lim=b;i<=lim;i++)
#define Rep(i,a,b)	for(int i=a,lim=b;i>=lim;i--)

#define	fi	first
#define se	second
#define MK	make_pair
#define PA	pair<int, int>

//#define	min(a,b)	((a)<(b)?(a):(b))
//#define	max(a,b)	((a)<(b)?(b):(a))

#define	CH	(ch=getchar())
int		IN()	{
		int x= 0, f= 0, ch;
		for	(; CH < '0' || ch > '9';)	f= (ch == '-');
		for	(; ch >= '0' && ch <= '9'; CH)	x= x*10 + ch -'0';
		return	f? -x : x;
}

const int N = 60;

bool G[N][N], vis[N]; int p[N];
int n;

#define REP(i, b)	for (int i= 0; i < b ;i++)

bool dfs(int x){	//DFS
    REP(y, n) if (!vis[y] && G[x][y]){
        vis[y] = true;
        if (p[y] == -1 || dfs(p[y])){
            p[y] = x;
            return true;
        }
    }
    return false;
}

int max_match(){	//匈牙利求二分图匹配
    int res = 0;
	REP(i, n)	p[i]= -1;
	
	REP(i, n){
		REP(j, n)	vis[j]= 0;
        if (dfs(i)) ++res;
    }
    return res;
}

class Incubator {
public:
    int maxMagicalGirls(vector <string> love) {
        n = love.size(); REP(i ,n)	REP(j, n)	G[i][j] = love[i][j] == 'Y';
        REP(k, n)	REP(i ,n)	REP(j, n) G[i][j] = G[i][j] || (G[i][k] && G[k][j]);	//floyed求传递闭包
        return n - max_match();
    }
};