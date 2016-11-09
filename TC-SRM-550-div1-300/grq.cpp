#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

int n,v[4][2]={1,0,0,1,-1,0,0,-1};
bool vis[5005][5005];

class RotatingBot{
public:
	int minArea(vector <int> moves){
		n=moves.size();
		int now=3,x=0,y=0;//now:方向 x,y:坐标 
		vis[x+2500][y+2500]=1;//vis:记过每个位置是否经过 
		int a=0,b=0,c=0,d=0;//a:左边界 b:右边界 c:下边界 d:上边界 
		for(int i=0;i<n;i++){
			now=(now+1)&3;
			for(int j=0;j<moves[i];j++){
				x+=v[now][0],y+=v[now][1];
				if(vis[x+2500][y+2500]) return -1;//判断是否经过 
				vis[x+2500][y+2500]=1;
			}
			if(!a&&x<0) a=x;
			if(!b&&x>0) b=x;
			if(!c&&y<0) c=y;
			if(!d&&y>0) d=y;//建立边界 
			if(now==0&&x<b&&!vis[x+2501][y+2500]&&i!=n-1) return -1;
			if(now==2&&x>a&&!vis[x+2499][y+2500]&&i!=n-1) return -1;
			if(now==1&&y<d&&!vis[x+2500][y+2501]&&i!=n-1) return -1;
			if(now==3&&y>c&&!vis[x+2500][y+2499]&&i!=n-1) return -1;//判断是否满足到头转90度的条件
			if(a&&x<a) return -1;
			if(b&&x>b) return -1;
			if(c&&y<c) return -1;
			if(d&&y>d) return -1;//判断是否超出边界 
			
		}
		return  (b-a+1)*(d-c+1);
	}
};