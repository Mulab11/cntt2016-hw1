// FST:分类讨论一种特殊情况判错FST一次，一种情况把变量名打错又FST一次
#include <vector>
#include <string>
#define X(x,y) ((x)>=0&&(x)<R&&(y)>=0&&(y)<C&&frame[x][y]=='X')
using namespace std;
class Tunnels{
public:
	bool left_in[60],left_out[60],right_in[60],right_out[60],is_line[60],vis[60][60][60]; // 0表示无，1表示有
	int dis[60][60][60];
	int min(int a,int b){return a<b?a:b;}
	int dfs(int i,int m,int s1,int s2){ // 计算还需要多少条路径
		if(i==m)return 0;
		if(vis[i][s1][s2])return dis[i][s1][s2];
		vis[i][s1][s2]=1;
		dis[i][s1][s2]=is_line[i]?
			min(dfs(i+1,m,s1?s1-1:0,s2+1)+!s1,dfs(i+1,m,s1+1,s2?s2-1:0)+!s2):
			dfs(i+1,m,s1||!left_in[i]?s1+(left_in[i]?-1:left_out[i]?1:0):0,s2||!right_in[i]?s2+(right_in[i]?-1:right_out[i]?1:0):0)+(!s1&&left_in[i])+(!s2&&right_in[i]);
		return dis[i][s1][s2];
	}
	int minimumTunnels(vector <string> frame){
		int R=frame.size(),C=frame[0].length(),vx[4]={-1,0,0,1},vy[4]={0,-1,1,0},ans=0;
		if(C==1){ // 特判只有一列的情况
			for(int i=0;i<R;i++)if(X(i,0))return 1;
			return 0;
		}
		for(int i=0;i<R;i++)for(int j=0;j<C;j++)if(X(i,j)){ // 找出所有区域内的路径 
			int deg=0;
			for(int d=0;d<4&&deg<2;d++)if(X(i+vx[d],j+vy[d]))deg++;
			if(deg==2)continue;
			int sx=i,sy=j,tx=i,ty=j,tmp;
			while(X(tx,ty)){
				frame[tx][ty]='.';
				for(int d=0;d<4;d++)if(X(tx+vx[d],ty+vy[d])){tx+=vx[d],ty+=vy[d];break;}
			}
			if(sx>tx||sx==tx&&sy>ty)tmp=sx,sx=tx,tx=tmp,tmp=sy,sy=ty,ty=tmp;
			// 判掉第一行的单个格子(会被处理成in=out=1)
			if(!sx&&!tx&&sy==ty){
				ans++;
				if(!sy)left_out[0]=1; // U->L
				else if(sy==C-1)right_out[0]=1; // U->R
			}
			else if(!sy){
				if(!ty)left_in[sx]=1,!sx||tx>sx+1?left_out[tx]=1:1; // L->L，非第一行且行差不大时转为L->D
				else if(ty==C-1)sx==tx?is_line[sx]=1:left_in[sx]=right_out[tx]=1; // L->R，可能在同一行
				else if(!tx)ans++,left_out[sx]=1; // L->U，转为U->L
				else left_in[sx]=1; // L->D
			}
			else if(sy==C-1){
				if(!ty)right_in[sx]=left_out[tx]=1; // R->L
				else if(ty==C-1)right_in[sx]=1,!sx||tx>sx+1?right_out[tx]=1:1; // R->R，非第一行且行差不大时转为R->D
				else right_in[sx]=1; // R->D
			}
			else if(!sx){
				ans++;
				if(!ty)left_out[tx]=1; // U->L
				else if(ty==C-1)right_out[tx]=1; // U->R
			}
			else if(!ty)left_in[tx]=1; // D->L，转为L->D
			else if(ty==C-1)right_in[tx]=1; // D->R，转为R->D
		}
		return ans+dfs(0,R,0,0);
	}
};
