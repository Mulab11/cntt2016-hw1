/*
每个位置可能会被它左上方的元素覆盖。
计算每个位置没有被覆盖的次数即可。 
*/

#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class PastingPaintingDivOne{
	private:
		static const int maxn=55;
		int dis[maxn][maxn];
	
	public:
		vector<long long> countColors(vector<string> clipboard, int T){
			vector<long long> ret{0,0,0};
			int n=clipboard.size();
			int m=clipboard[0].length();
			
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j){
				if (i==0||j==0) dis[i][j]=T;
				else {
					if (clipboard[i-1][j-1]=='.') dis[i][j]=min(T,dis[i-1][j-1]+1);
					else dis[i][j]=1;
				}
				
				if (clipboard[i][j]=='R') ret[0]+=dis[i][j];
				else if (clipboard[i][j]=='G') ret[1]+=dis[i][j];
				else if (clipboard[i][j]=='B') ret[2]+=dis[i][j];
			}
			
			return ret;
		}
};
