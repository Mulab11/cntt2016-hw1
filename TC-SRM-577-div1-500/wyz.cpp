// BEGIN CUT HERE

// END CUT HERE
#line 5 "EllysChessboard.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

void Min(int &x,int y){if (x<0||y<x) x=y;}

const int maxn=70;
const int b=16;

class EllysChessboard{
	int x[maxn],y[maxn],n;
	bool valid[maxn];
	int dp[17][17][17][17];
	public:
	int minCost(vector <string> board){
		n=0;
		memset(dp,-1,sizeof(dp));
		for (int i=0;i<board.size();++i)
			for (int j=0;j<board[i].size();++j)
				if (board[i][j]=='#'){
					x[n]=i+j;
					y[n]=i-j+b/2-1;
//					printf("%d %d\n",x[n],y[n]);
					dp[x[n]][x[n]][y[n]][y[n]]=0;
					n++;
				}
		int ret=0;
		for (int lx=b-1;lx>=0;--lx)for (int rx=lx;rx<b;++rx)
			for (int ly=b-1;ly>=0;--ly)for (int ry=ly;ry<b;++ry)if (dp[lx][rx][ly][ry]>=0){
				memset(valid,0,sizeof(valid));
				bool flag=0;
				for (int i=0;i<n;++i)if (x[i]<lx||x[i]>rx||y[i]<ly||y[i]>ry)
					flag=valid[i]=1;
				if (!flag){ret=dp[lx][rx][ly][ry];break;}
				
				for (int i=0;i<n;++i)if (valid[i]){
					int LX=min(lx,x[i]);
					int RX=max(rx,x[i]);
					int LY=min(ly,y[i]);
					int RY=max(ry,y[i]);
					int cost=0;
					for (int j=0;j<n;++j)if (valid[j]){
						if (x[j]<LX||x[j]>RX||y[j]<LY||y[j]>RY)continue;
						cost+=max(max(RX-x[j],x[j]-LX),max(RY-y[j],y[j]-LY));
					}
//					if (LX==4&&RX==11&&LY==4&&RY==9) printf("%d %d %d %d\n",lx,rx,ly,ry);
					Min(dp[LX][RX][LY][RY],dp[lx][rx][ly][ry]+cost);
				}
			}
		return ret;
	}
};
