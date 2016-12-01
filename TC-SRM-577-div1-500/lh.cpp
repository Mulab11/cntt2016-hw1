#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>
using namespace std;

class EllysChessboard{
	static const int maxn=15,inf=0x3f3f3f3f;
		int dp[maxn][maxn][maxn][maxn];
		bool mp[maxn][maxn];
	public:
		int minCost(vector<string> B){
			memset(dp,0x3f,sizeof dp);
			int top=0,blw=100,lft=100,rit=0;
			bool fl=true;
			for(int i=0;i<8;++i)
			for(int j=0;j<8;++j) if(B[i][j]=='#'){
				fl=false;
				int x=i-j+7,y=i+j;
				if (rit<x) rit=x;
				if (lft>x) lft=x;
				if (top<y) top=y;
				if (blw>y) blw=y;
				dp[x][x][y][y]=0;
				mp[x][y]=true;
			}
			if (fl) return 0;
			for(int w=0;w<=rit-lft;++w)
			for(int h=0;h<=top-blw;++h)
			for(int l=lft;l+w<=rit;++l)
			for(int b=blw;b+h<=top;++b){
				int r=l+w,t=b+h;
				if(dp[l][r][b][t]<inf){
					for(int x=lft;x<=rit;++x)
					for(int y=blw;y<=top;++y) if (x<l||x>r||y<b||y>t) if (mp[x][y]){
						int tmp=dp[l][r][b][t]+max(max(x-l,r-x),max(y-b,t-y));
						int mx1=max(x,r),mx2=max(y,t);
						int mn1=min(x,l),mn2=min(y,b);
						for(int i=mn1;i<=mx1;++i)
						for(int j=mn2;j<=mx2;++j) if (i<l||i>r||j<b||j>t)
						if(mp[i][j]&&(i!=x||j!=y))
							tmp+=max(max(i-mn1,mx1-i),max(j-mn2,mx2-j));
						if (dp[mn1][mx1][mn2][mx2]>tmp) dp[mn1][mx1][mn2][mx2]=tmp;
					}
				}
			}
			return dp[lft][rit][blw][top];
		}
};
