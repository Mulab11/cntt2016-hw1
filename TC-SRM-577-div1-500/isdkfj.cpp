#include <bits/stdc++.h>

using namespace std;

int f[15][15][15][15];

int cost(int x,int y,int p1,int p2,int q1,int q2){//代价 
	return max(max(abs(x+y-p1),abs(x+y-p2)),max(abs(x-y-q1),abs(x-y-q2)));
}

class EllysChessboard {
public:
	int minCost(vector <string> board) {
		memset(f,0x3f,sizeof f);
		for(int x=0;x<8;++x)
			for(int y=0;y<8;++y)if(board[x][y]=='#')
				f[x+y][x+y][x-y+7][x-y+7]=0;//初始化 
		for(int p1=0;p1<=14;++p1)//max(x+y)
			for(int p2=p1;p2>=0;--p2)//min(x+y)
				for(int q1=-7;q1<=7;++q1)//max(x-y)
					for(int q2=q1;q2>=-7;--q2){//min(x-y)
						int d=f[p1][p2][q1+7][q2+7];
						if(d<=10000000){
							for(int x=0;x<8;++x)
								for(int y=0;y<8;++y)if(board[x][y]=='#'&&(x+y>p1||x+y<p2||x-y>q1||x-y<q2)){
									//枚举接下去放哪个点 
									int tmp=d;
									int r1=max(p1,x+y),r2=min(p2,x+y),s1=max(q1,x-y),s2=min(q2,x-y);
									int&u=f[r1][r2][s1+7][s2+7];
									for(int i=0;i<8;++i)
										for(int j=0;j<8;++j)
										if(board[i][j]=='#'&&(i+j>p1||i+j<p2||i-j>q1||i-j<q2)&&i+j<=r1&&i+j>=r2&&i-j<=s1&&i-j>=s2)
										tmp+=cost(i,j,r1,r2,s1,s2);//能放的都放了 
									if(tmp<u)u=tmp;
								}
						}
					}
		int p1=0,p2=14,q1=-7,q2=7;
		for(int i=0;i<8;++i)
			for(int j=0;j<8;++j)
			if(board[i][j]=='#'){
				p1=max(p1,i+j);
				p2=min(p2,i+j);
				q1=max(q1,i-j);
				q2=min(q2,i-j);
			}
		if(p1<p2)return 0;//特判棋盘为空 
		return f[p1][p2][q1+7][q2+7];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
