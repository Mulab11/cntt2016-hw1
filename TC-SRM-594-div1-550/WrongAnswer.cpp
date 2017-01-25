#include <vector>
#include <string>
#include <cstring>
#define P(i,j) ((i)*C+(j)+2)
using namespace std;
class Netflow{
public:
	struct edge{int to,cap;edge*rev,*next;}E[25100],*ne,*first[2510],*cur[2510];
	void init(){ne=E;memset(first,0,sizeof(first));}
	void link(int a,int b,int c){
		*ne=(edge){b,c,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,0,ne-1,first[b]};first[b]=ne++;
	}
	int Q[2510],D[2510];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next)if(e->cap&&D[e->to]==D[i]-1&&(f=dfs(e->to,c<e->cap?c:e->cap))){
			flow+=f;e->cap-=f;e->rev->cap+=f;if(!(c-=f))return flow;
		}
		return flow;
	}
	int maxflow(){
		for(int f=0;;f+=dfs(0,1<<30)){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
		}
	}
}solver;
class FoxAndGo3{
public:
	int maxEmptyCells(vector <string> board){
		int R=board.size(),C=board[0].length(),cnt=0,vx[4]={-1,0,0,1},vy[4]={0,-1,1,0};
		solver.init();
		for(int i=0;i<R;i++)for(int j=0;j<C;j++){
			if(board[i][j]=='.')solver.link(0,P(i,j),1),cnt++;
			else if(board[i][j]=='o'){
				solver.link(P(i,j),1,1);cnt++;
				for(int d=0,dx,dy;d<4;d++)if((dx=i+vx[d])>=0&&dx<R&&(dy=j+vy[d])>=0&&dy<C&&board[dx][dy]=='.')solver.link(P(dx,dy),P(i,j),1<<30);
			}
		}
		return cnt-solver.maxflow();
	}
};
