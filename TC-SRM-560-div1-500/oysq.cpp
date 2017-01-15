#line 2 "DrawingPointsDivOne.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;
const int S = 300;

int n;
int g[S + 9][S + 9];// 初始矩阵
int p[2][S + 9][S + 9];// 滚动数组节省空间

bool check(int step) {// step 二分的答案
	memcpy(p[0], g, sizeof g);
	// 以下为反向还原
	for(int i = 1; i <= step; ++i) {
		int a = i & 1, b = a ^ 1;
		memset(p[a], 0, sizeof p[a]);
		for(int x = 0; x <= S; ++x)
			for(int y = 0; y <= S; ++y)
				if(p[b][x][y])
					p[a][x][y] = p[a][x + 1][y] = p[a][x][y + 1] = p[a][x + 1][y + 1] = 1;
	}
	// 以下为正向模拟
	for(int i = step - 1; i >= 0; --i) {
		int a = i & 1, b = a ^ 1;
		memset(p[a], 0, sizeof p[a]);
		for(int x = 0; x <= S; ++x)
			for(int y = 0; y <= S; ++y)
				p[a][x][y] = p[b][x][y] & p[b][x + 1][y] & p[b][x][y + 1] & p[b][x + 1][y + 1];
	}
	// 检测是否与原矩阵相同
	for(int x = 0; x <= S; ++x)
		for(int y = 0; y <= S; ++y)
			if(p[0][x][y] != g[x][y])
				return false;
	return true;
}

class DrawingPointsDivOne {  
public:  
	int maxSteps(vector <int> x, vector <int> y) {  
		n = SZ(x);
		memset(g, 0, sizeof g);
		for(int i = 0; i < n; ++i)
			g[x[i] + 70][y[i] + 70] = 1;// 将坐标变成非负
		// 二分答案
		int l = 0, r = 150;
		while(l < r) {
			int mid = (l + r + 1) >> 1;
			if(check(mid)) l = mid;
			else r = mid - 1;
		}
		if(l == 150) return -1;// 没有最大值
		else return l;
	}  
};
