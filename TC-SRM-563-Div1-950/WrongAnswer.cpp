// FST:判断a,b属于不同状态只判了a仍在棋盘b移出棋盘，没判b仍在棋盘a移出棋盘 
#include <vector>
#include <string>
#define MOD 1000000009
using namespace std;
class CoinsGame{
public:
	int R,C,tot,id[42][42],vx[4]={-1,0,0,1},vy[4]={0,-1,1,0},pow2[1610];
	vector<int>trans[1610][4];
	bool vis[1610][1610],del[1610];
	struct item{short a,b;}Q[1610*1610],*H,*T;
	int ways(vector <string> board){
		R=board.size();C=board[0].length();
		for(int x=0;x<R;x++)
			for(int y=0;y<C;y++)if(board[x][y]=='.')id[x][y]=++tot;
		for(int x=0;x<R;x++)
			for(int y=0,i;y<C;y++)if(i=id[x][y])
				for(int d=0,dx,dy;d<4;d++)trans[(dx=x+vx[d])>=0&&dx<R&&(dy=y+vy[d])>=0&&dy<C?id[dx][dy]?id[dx][dy]:i:0][d].push_back(i);
		for(int s=1;s<=tot;s++)
			for(int t=0;t<2;t++)if(!vis[t?s:0][t?0:s])
				for(*Q=(item){t?s:0,t?0:s},H=Q,T=Q+1;H<T;H++)
					for(int d=0;d<4;d++)
						for(int i=trans[H->a][d].size();i--;)
							for(int j=trans[H->b][d].size();j--;)
								if(!vis[T->a=trans[H->a][d][i]][T->b=trans[H->b][d][j]])vis[T->a][T->b]=1,T++;
		for(int i=*pow2=1;i<=tot;i++)pow2[i]=pow2[i-1]*2%MOD;
		int ans=pow2[tot]-1;
		for(int i=1;i<=tot;i++)if(!del[i]){
			int siz=0;
			for(int j=1;j<=tot;j++)!vis[i][j]?siz++,del[j]=1:1;
			ans=(ans+MOD-pow2[siz]+1)%MOD;
		}
		return ans;
	}
};
