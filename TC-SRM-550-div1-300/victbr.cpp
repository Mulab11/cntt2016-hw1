#include <bits/stdc++.h>

using namespace std;

class RotatingBot{
	public:
		int a[2510][2510];
		int minArea(vector <int> moves){
			memset(a,0,sizeof(a));
			a[1250][1250] = 1;
			int mxx = 1250,mxy = 1250,mnx = 1250,mny = 1250;
			int x = 1250,y = 1250,u = 1,v = 0,cnt = 0;
			for (int i = 0;i < moves.size();i++){
				for (int j = 1;j <= moves[i];j++){
					x += u;y += v;
					if (a[x][y] == 1) return -1;
					if (a[x][y] == 2) return -1;
					a[x][y] = 1;
				}
				mxx = max(mxx,x);
				mxy = max(mxy,y);
				mnx = min(mnx,x);
				mny = min(mny,y);				
				if (a[x+u][y+v] == 0 && i != moves.size()-1) {
					cnt++;
					a[x+u][y+v] = 2;
				}
				swap(u,v);u = -u;
			}
			for (int i = mnx;i <= mxx;i++){
				if (a[i][mxy+1] == 2) cnt--;
				if (a[i][mny-1] == 2) cnt--;
			}
			for (int i = mny;i <= mxy;i++){
				if (a[mxx+1][i] == 2) cnt--;
				if (a[mnx-1][i] == 2) cnt--;
			}
			if (cnt) return -1; 
	
			return (mxx-mnx+1)*(mxy-mny+1);
		}
};
