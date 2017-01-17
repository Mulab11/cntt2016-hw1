/*
	对于答案k，进行k次逆操作后判断是否可以还原。
	可以还原当且仅当还原后点数相同。 
	显然答案可以二分 
*/ 
#include <bits/stdc++.h>

using namespace std;

const int N = 410;
 
class DrawingPointsDivOne{
	public:
		int n,f[N][N],g[N][N];
		int maxSteps(vector<int> x, vector<int> y){
			n = x.size();
			for (int i = 0;i < n;i++)
				x[i] += 71,y[i] += 71;
			/*
				当扩成凸多边形时，将可以无限扩大。
				如果非凸，因为每扩一次距离减一，所以至多139次后就会变成凸的  
			*/ 
			int l = 0,r = 200,mid = (l+r+1) >> 1;
			while (l < r){
				if (check(mid,x,y)) l = mid;
				else r = mid-1;
				mid = (l+r+1)>>1;
			}
			if (l == 200) return -1;
			else return l;
		}
		bool check(int k,vector<int> x, vector<int> y){
			int cnt = 0;
			memset(f,0,sizeof(f));
			memset(g,0,sizeof(g));
			k++;
			/*
				k次逆操作后，每个点形成一个k*k的点阵，k次逆操作后剩下的点将在大于k的操作时消除。
				为了方便处理，直接另k=k++ 
			*/
			/*
				二维差分 
			*/
			for (int i = 0;i < n;i++){
				f[x[i]][y[i]]++;
				f[x[i]+k][y[i]+k]++;
				f[x[i]+k][y[i]]--;
				f[x[i]][y[i]+k]--;
			}
			for (int i = 1;i <= 400;i++)
				for (int j = 1;j <= 400;j++)
					f[i][j] += f[i-1][j]+f[i][j-1]-f[i-1][j-1];
			for (int i = 1;i <= 400;i++)
				for (int j = 1;j <= 400;j++)
					if (f[i][j] == 0) g[i][j] = 0;
					else{
						int m = min(min(g[i-1][j],g[i][j-1]),g[i-1][j-1]);
						g[i][j] = m+1;
						if (g[i][j] >= k) cnt++;
					}
			return cnt == n;
		}
};
