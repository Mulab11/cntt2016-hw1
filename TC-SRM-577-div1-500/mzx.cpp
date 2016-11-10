#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>

const int n(15);
inline void cmin(int& a,int b){if(a>b)a=b;}
inline void cmax(int& a,int b){if(a<b)a=b;}
class EllysChessboard{
	private:
		int f[n][n][n][n];//DP数组,f[xl][xr][yl][yl]代表取完[xl,xr][yl,yr]这个矩形内所有点的最小代价
	public:
		int minCost(std::vector<std::string> board){
			using std::min;using std::max;
			memset(f,1,sizeof f);
			int mnx=15,mxx=0,mny=15,mxy=0;
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
					if(board[i][j]=='#'){
						int x=i-j+7,y=i+j;//新坐标
						cmin(mnx,x),cmax(mxx,x);
						cmin(mny,y),cmax(mxy,y);
						f[x][x][y][y]=0;//初始化新棋盘
					}
			if(mnx>mxx)return 0;//没有棋子代价为0
			#define in(x,y) ( (xl-(x))*(xr-(x))<=0 && (yl-(y))*(yr-(y))<=0 )
			for(int xn=0;xn<n;xn++)//枚举矩形的横长
			for(int yn=0;yn<n;yn++)//纵长
				for(int xl=0,xr=xl+xn;xr<n;xl++,xr++)//枚举矩形的左上角横坐标
				for(int yl=0,yr=yl+yn;yr<n;yl++,yr++)//纵坐标
				if(f[xl][xr][yl][yr]<=1000)
					for(int nx=0;nx<n;nx++)//枚举新取的点的横坐标
					for(int ny=0;ny<n;ny++)//纵坐标
					if(!in(nx,ny)&&!f[nx][nx][ny][ny]){//如果这个点不在当前矩形内且有棋子
						int cost=f[xl][xr][yl][yr]+max(max(nx-xl,xr-nx),max(ny-yl,yr-ny)),//初始化代价
							nxl=min(xl,nx),nxr=max(xr,nx),//新矩形的横区间
							nyl=min(yl,ny),nyr=max(yr,ny);//纵区间
						for(int i=nxl;i<=nxr;i++)//枚举横纵标
						for(int j=nyl;j<=nyr;j++)//纵坐标
						if(!in(i,j)&&!f[i][i][j][j]&&(i!=nx||j!=ny))//如果此处有棋子且不在原矩形内
							cost+=max(max(i-nxl,nxr-i),max(j-nyl,nyr-j));//计算在新矩形的边界下取该棋子的代价
						cmin(f[nxl][nxr][nyl][nyr],cost);//更新状态最优值
					}
			return f[mnx][mxx][mny][mxy];
		}
};
/*
#define FILE "500pts"
#define gc() getchar()
std::vector<std::string> map;
EllysChessboard test;
void init(){
	char c=gc();
	do{
		std::string s;
		while(c!='"')
			c=gc();
		c=gc();
		while(c!='"')
			s=s+c,c=gc();
		c=gc();
		map.push_back(s);
	}while(c!='}');
}
int main(){
	freopen(FILE".in","r",stdin);
	//freopen(FILE".out","w",stdout);
	init();
	printf("Answer=%d\n",test.minCost(map));
	return 0;
}*/
