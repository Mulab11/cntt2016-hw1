#include <bits/stdc++.h>

using namespace std;

const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
set<pair<int,int> >s;
#define mp make_pair

class RotatingBot {
public:
	int minArea(vector <int> moves) {
		int n=moves.size();
		int x1=0,x2=0,y1=0,y2=0,x=0,y=0,f=0;
		for(int i=0;i<n;++i){//求x,y的最大值与最小值 
			x+=dx[f]*moves[i];
			y+=dy[f]*moves[i];
			if(x<x1)x1=x;if(x>x2)x2=x;
			if(y<y1)y1=y;if(y>y2)y2=y;
			f=(f+1)%4;
		}
		x=y=f=0;
		s.insert(mp(x,y));
		for(int i=0,xx,yy;i<n;++i){
			for(int j=0;j<moves[i];++j){//模拟每个点，判断是否重复 
				x+=dx[f];y+=dy[f];
				if(s.find(mp(x,y))!=s.end())return -1;
				s.insert(mp(x,y));
			}
			xx=x+dx[f];yy=y+dy[f];
			if(i<n-1&&x1<=xx&&xx<=x2&&y1<=yy&&yy<=y2&&s.find(mp(xx,yy))==s.end())return -1;
			//如果出现奇怪的拐弯就返回-1 
			f=(f+1)%4;
		}
		return (x2-x1+1)*(y2-y1+1);
	}
};




//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
