#include <vector>
#include <string>
#include <cstring>
using namespace std;
class TheTilesDivOne{
public:
	struct edge{int to,cap;edge*rev,*next;}E[13824],*ne,*first[3456],*cur[3456];
	void link(int a,int b,int d=1){
		*ne=(edge){b,d,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,!d,ne-1,first[b]};first[b]=ne++;
	}
	int Q[3456],D[3456];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next)if(e->cap&&D[e->to]==D[i]-1&&(f=dfs(e->to,c<e->cap?c:e->cap))){
			flow+=f;e->cap-=f;e->rev->cap+=f;
			if(!(c-=f))return flow;
		}
		return flow;
	}
	int maxflow(){
		for(int f=0;;){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
			f+=dfs(0,1<<30);
		}
	}
	int P[48][48];
	bool ex(int i,int j){return i>=0&&j>=0&&P[i][j];}
	int find(vector <string> board){
		int R=board.size(),C=board[0].length(),tot=2;ne=E;
		memset(first,0,sizeof(first));memset(P,0,sizeof(P));
		for(int i=0;i<R;i++)for(int j=(i+1)%2;j<C;j+=2)if(board[i][j]!='X')
			i%2?link(0,tot):link(tot,1),P[i][j]=tot++;
		for(int i=0;i<R;i++)for(int j=i%2;j<C;j+=2)if(board[i][j]!='X'){
			if(ex(i,j-1))link(P[i][j-1],tot,j%2);
			if(ex(i,j+1))link(P[i][j+1],tot,j%2);
			tot++;link(tot-1,tot,j%2);
			if(ex(i-1,j))link(tot,P[i-1][j],j%2);
			if(ex(i+1,j))link(tot,P[i+1][j],j%2);
			tot++;
		}
		return maxflow();
	}
};
