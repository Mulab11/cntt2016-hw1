// Unsolved:没有推出结论，看了题解
#include <vector>
#include <string>
#define fe(x0,y0) for(int d=0,dx,dy;d<4;d++)if((dx=x0+vx[d])>=0&&dx<R&&(dy=y0+vy[d])>=0&&dy<C&&field[dx][dy]!='#')
#define fc(x0,y0) fe(x0,y0)if((t?DB:DA)[dx][dy]>(t?DB:DA)[x0][y0])
using namespace std;
class GameInDarknessDiv1{
public:
	int DA[55][55],DB[55][55],up[55][55],down[55][55],se[55][55],vis[55][55],vx[4]={-1,0,0,1},vy[4]={0,-1,1,0};
	struct item{int x,y;}Q[2555],*H,*T;
	int max(int a,int b){return a>b?a:b;}
	void cmax(int&a,int&b,int c){c>a?b=a,a=c:c>b?b=c:1;}
	string check(vector <string> field){
		int R=field.size(),C=field[0].length(),xA,yA,xB,yB;
		for(int x=0;x<R;x++)
			for(int y=0;y<C;y++)field[x][y]=='A'?xA=x,yA=y:field[x][y]=='B'?xB=x,yB=y:1;
		for(int t=0;t<2;t++){
			for(*Q=(item){t?xB:xA,t?yB:yA},H=Q,T=Q+1,vis[Q->x][Q->y]=!t;H<T;up[H->x][H->y]=down[H->x][H->y]=0,H++)
				fe(H->x,H->y)if(vis[dx][dy]==t)vis[T->x=dx][T->y=dy]=!t,(t?DB:DA)[dx][dy]=(t?DB:DA)[H->x][H->y]+1,T++;
			while(H-->Q)fc(H->x,H->y)cmax(down[H->x][H->y],se[H->x][H->y],down[dx][dy]+1);
			for(H=Q;H<T;H++)fc(H->x,H->y)up[dx][dy]=max(up[H->x][H->y],down[H->x][H->y]==down[dx][dy]+1?se[H->x][H->y]:down[H->x][H->y])+1;
		}
		for(int x=0,t=1;x<R;x++)for(int y=0;y<C;y++)if(DA[x][y]-DB[x][y]>1){
			int cnt=up[x][y]>2;
			fc(x,y)if(down[dx][dy]>1)cnt++;
			if(cnt>2)return "Bob wins";
		}
		return "Alice wins";
	}
};
