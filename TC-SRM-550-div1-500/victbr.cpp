#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

class CheckerExpansion{
	public:
		bool b[60];
		vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h){
			vector <string> ans,ans2;
			
			string s = "";
			for (int i = 1;i <= w;i++) s += '.'; 
			for (int i = 1;i <= h;i++) ans.push_back(s);
			for (int i = 0;i < w;i++)
				for (int j = 0;j < h;j++){
					ll u = x0+i,v = y0+j;
					if (u+v >= t*2) continue;
					if ((u+v)&1) continue;
					memset(b,0,sizeof(b));
					for (long long k = 1,l = 0;k <= 1e12;k <<= 1,l++)
						if (v&k){v -= k;u -= k;b[l] = 1;}
					for (long long k = 1,l = 0;k <= 1e12;k <<= 1,l++)
						if ((u&(k*2))&&b[l] == 0)u -= k*2;					
					
					
					
					if (u == 0 && v == 0) {
						u = x0+i;v = y0+j;
						ans[j][i] = (u+v)%4 ? 'B' : 'A';
					}
				}
			for (int i = 0;i < h;i++) ans2.push_back(ans[h-i-1]);
			return ans2;
		}
};
