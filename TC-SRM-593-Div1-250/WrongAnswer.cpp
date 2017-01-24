#include <vector>
#include <string>
#include <cstdio>
using namespace std;
class HexagonalBoard{
public:
	int minColors(vector <string> board){
		bool k[4]={1,1,1,1};
		int N=board.size(),Qx[2510],Qy[2510],head,tail,vx[6]={-1,-1,0,0,1,1},vy[6]={0,1,-1,1,-1,0};
		for(int x=0;x<N;x++)
			for(int y=0;y<N;y++)if(board[x][y]=='X')
				for(board[*Qx=x][*Qy=y]=head=*k=0,tail=1;head<tail;head++)
					for(int d=0,dx,dy;d<6;d++)if((Qx[tail]=dx=Qx[head]+vx[d])>=0&&dx<N&&(Qy[tail]=dy=Qy[head]+vy[d])>=0&&dy<N)
						board[dx][dy]=='X'?k[1]=0,board[dx][dy]=!board[Qx[head]][Qy[head]],tail++:board[dx][dy]==board[Qx[head]][Qy[head]]?k[2]=0:1;
		for(int i=0;;i++)if(k[i])return i;
	}
};
