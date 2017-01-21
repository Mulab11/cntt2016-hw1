// BEGIN CUT HERE

// END CUT HERE
#line 5 "RotatingBot.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=5003;

class RotatingBot{
	bool vis[maxn][maxn];
	public:
	int minArea(vector <int> moves){
		int bound[4]={-1,-1,-1,-1};
		int x=2500,y=2500;
		int mnx=x,mxx=x,mny=y,mxy=y;
		memset(vis,0,sizeof(vis));
		const int dx[4]={1,0,-1,0};
		const int dy[4]={0,1,0,-1};
		int k=0;
		vis[x][y]=1;
		for (int i=0;i<moves.size();++i,(++k)&=3){
			int step=moves[i];
			for (int i=0;i<step;++i){
				x+=dx[k];y+=dy[k];
				if (vis[x][y]) return -1;
				vis[x][y]=1;
			}
			mnx=min(mnx,x);
			mxx=max(mxx,x);
			mny=min(mny,y);
			mxy=max(mxy,y);
			if (i==moves.size()-1) break;
			int tmp=dx[k]?x+dx[k]:(y+dy[k]);
			if (vis[x+dx[k]][y+dy[k]]);
			else if (bound[k]<0||bound[k]==tmp) bound[k]=tmp;
			else return -1;
		}
		if (bound[0]>=0&&bound[0]<mxx+1) return -1;
		if (bound[1]>=0&&bound[1]<mxy+1) return -1;
		if (bound[2]>=0&&bound[2]>mnx-1) return -1;
		if (bound[3]>=0&&bound[3]>mny-1) return -1;
		
		if (bound[0]<0) bound[0]=mxx+1;
		if (bound[1]<0) bound[1]=mxy+1;
		if (bound[2]<0) bound[2]=mnx-1;
		if (bound[3]<0) bound[3]=mny-1;
		return (bound[0]-bound[2]-1)*(bound[1]-bound[3]-1);
	}
};
