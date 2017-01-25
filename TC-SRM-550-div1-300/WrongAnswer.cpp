// FST:理解错题意后来改过来的时候一个<=打成<
#include <vector>
using namespace std;
class RotatingBot{
public:
	char vis[5010][5010];
	int u,d,l,r;
	int minArea(vector <int> moves){
		int vx[4]={0,-1,0,1},vy[4]={1,0,-1,0},x=2502,y=2502;u=x,d=x,l=y,r=y;
		for(int i=0,D=0;i<moves.size();i++,D=(D+1)%4){
			// 模拟每次的移动
			for(int t=0;t<moves[i];t++){
				vis[x][y]=1;
				x+=vx[D];y+=vy[D];
				if(vis[x][y])return -1; // 遇到之前走过的格子就不合法
			}
			x<u?u=x:x>d?d=x:1;
			y<l?l=y:y>r?r=y:1;
		}
		// 之前理解错题目，实际上每次要走到不能走为止
		x=y=2502;
		for(int i=0,D=0;i<moves.size();i++,D=(D+1)%4){
			for(int t=0;t<moves[i];t++){
				vis[x][y]=2;
				x+=vx[D];y+=vy[D];
				if(vis[x][y]==2)return -1;
			}
			if(i<moves.size()-1&&vis[x+vx[D]][y+vy[D]]!=2&&x+vx[D]>=u&&x+vx[D]<=d&&y+vy[D]>=l&&y+vy[D]<=r)return -1; // 如果还能走说明不合法
		}
		return (d-u+1)*(r-l+1); // 合法，输出最小面积
	}
};
