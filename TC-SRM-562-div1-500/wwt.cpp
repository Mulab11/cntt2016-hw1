/*
我们要判断是否存在不合法的凸多边形。那么相当于枚举一条对角线(x,y)，满足x和y都是白色的，然后判断是否存在(p,q)使得p,q都是黑色，
p在(x,y)左侧，q在(x,y)右侧，且x在pq左侧，y在pq右侧。那么我们可以先预处理lef[x][p][q]表示x是否在p,q右侧，rig[x][p][q]同理，
把[q]这一维用bitset压掉。然后再枚举x,y，枚举p，另外存一个right[q]表示q是否在x->y右侧，最后lef[x][p]&rig[y][p]&right看看是否不为空即可
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node
{
	ll x,y;

	node(void){}
	node(int a,int b):x(a),y(b){}
};

node operator -(const node &a,const node &b) {return node(a.x - b.x,a.y - b.y);}
ll operator ^(const node &a,const node &b) {return a.x * b.y - a.y * b.x;}
ll operator *(const node &a,const node &b) {return a.x * b.x + a.y * b.y;}

bitset<225> lef[225][225],rig[225][225];

class CheckerFreeness
{
public:
	vector<node> w,b;

	void decode(vector<string> a,vector<int> &b)
	{
		b.clear();
		int v = 0;
		for(int i = 0;i < a.size();i ++)
			for(int j = 0;j < a[i].length();j ++)
			{
				if (a[i][j] >= '0' && a[i][j] <= '9') v = v * 10 + a[i][j] - '0'; else
				{
					if (v) b.push_back(v);
					v = 0;
				}
			}
		if (v) b.push_back(v);
	}

	string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY)
	{
		vector<int> wx,wy,bx,by;
		decode(whiteX,wx),decode(whiteY,wy),decode(blackX,bx),decode(blackY,by);
		w.clear(),b.clear();
		for(int i = 0;i < wx.size();i ++)
			w.push_back(node(wx[i],wy[i]));
		for(int i = 0;i < bx.size();i ++)
			b.push_back(node(bx[i],by[i]));
		for(int i = 0;i < b.size();i ++)
			for(int j = 0;j < b.size();j ++)
				if (i != j)
					for(int x = 0;x < w.size();x ++)
						if (((w[x] - b[i]) ^ (b[j] - b[i])) >= 0) //维护出左右的点
							rig[x][i][j] = 1; else
								lef[x][i][j] = 1; 
		for(int i = 0;i < w.size();i ++)
			for(int j = i + 1;j < w.size();j ++) //枚举对角线
			{
				bitset<225> up;
				up.reset();
				for(int k = 0;k < b.size();k ++)
					if (((b[k] - w[i]) ^ (w[j] - w[i])) < 0) up[k] = 1; //可以放上面
				for(int k = 0;k < b.size();k ++)
					if (((b[k] - w[i]) ^ (w[j] - w[i])) > 0)
						if ((up & lef[i][k] & rig[j][k]).count()) return "NO";						
			}
		return "YES";
	}
};
