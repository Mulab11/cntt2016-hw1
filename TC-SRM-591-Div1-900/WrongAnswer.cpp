#include <string>
#include <cstdio>
#define MOD 1000000009
using namespace std;
class StringPath{
public:
	int N,M,e[15];
	int f[8][8][1<<8][1<<8];
	int dfs(int x,int y,int S1,int S2){
		if(y==M)x++,y=0;
		if(x==N)return(S1>>M-1)&&(S2>>M-1);
		int&g=f[x][y][S1][S2],k1=S1>>y&1,k2=S2>>y&1,t1=k1||y&&(S1>>y-1&1),t2=k2||y&&(S2>>y-1&1);
		if(g)return g-1;
		g=(g+dfs(x,y+1,S1-(k1<<y),S2-(k2<<y))*(24ll+e[x+y]))%MOD;
		if(e[x+y])g=(g+dfs(x,y+1,S1+(t1<<y)-(k1<<y),S2+(t2<<y)-(k2<<y)))%MOD;
		else g=(g+dfs(x,y+1,S1+(t1<<y)-(k1<<y),S2-(k2<<y))+1ll*dfs(x,y+1,S1-(k1<<y),S2+(t2<<y)-(k2<<y)))%MOD;
		return g++;
	}
	int countBoards(int n, int m, string A, string B){
		N=n;M=m;
		for(int i=0;i<N+M-1;i++)e[i]=A[i]==B[i];
		return dfs(0,0,1,1);
	}
};
