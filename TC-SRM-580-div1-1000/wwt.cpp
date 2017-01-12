#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

int f[maxn][maxn][maxn][maxn]; //[y][x][x0][x1],the token is on (x,y),and the wall is under [x0,x1)

class WallGameDiv1
{
public:
	int c[maxn][maxn],n,m;

	int sum(int y,int x0,int x1) //count the sum in row y,[x0,x1)
	{
		int tmp = 0;
		for(;x0 < x1;x0 ++) tmp += c[y][x0];
		return tmp;
	}

	int aplay(int y,int x,int x0,int x1)
	{
		if (!(x >= x0 && x < x1)) return bplay(y + 1,x,x,x) + c[y + 1][x];//a can move downward
		//either move to x0 - 1 or x1
		return min(bplay(y,x0 - 1,x0,x1) + sum(y,x0 - 1,x),bplay(y,x1,x0,x1) + sum(y,x + 1,x1 + 1));
	}

	int bplay(int y,int x,int x0,int x1)
	{
		if (x < 0 || x >= m) return (1 << 30); //player a moves illegally
		int &tmp = f[y][x][x0][x1];
		if (tmp != -1) return tmp;
		if (y == n - 1) return 0;//a has been in bottom row
		//player b can choose not to place wall under x,so that a must move downward
		tmp = aplay(y,x,x0,x1);
		//player b must let player a be able to move 
		if (x1 - x0 < m - 1)
			tmp = max(tmp,aplay(y,x,min(x,x0),max(x + 1,x1)));//place wall under x
		return tmp;
	}

	int play(vector<string> cost)
	{
		n = cost.size(),m = cost[0].length();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++) c[i][j] = cost[i][j] - '0';
		int ans = (1 << 30);
		memset(f,255,sizeof f);
		for(int x = 0;x < m;x ++) //player a will choose a best position to start
			ans = min(ans,c[0][x] + bplay(0,x,x,x)); //we assume that x is among {x0,x0-1,x1,x1-1}
		return ans;
	}
};
