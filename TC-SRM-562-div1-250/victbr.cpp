#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 140;

class PastingPaintingDivOne{
	public:
		int w,h,a[N][N];
		ll sum[3];
		vector<long long> countColors(vector<string> clipboard, int T){
			vector <long long> ans;
			w = clipboard.size();
			h = clipboard[0].size();
			if (T <= min(h,w)){
				for (int i = 0;i < T;i++){
					for (int j = 0;j < w;j++)
						for (int k = 0;k < h;k++)
							if (clipboard[j][k] != '.'){
								if (clipboard[j][k] == 'R') sum[0]++;
								if (clipboard[j][k] == 'G') sum[1]++;
								if (clipboard[j][k] == 'B') sum[2]++;
								if (a[i+j][i+k] == 'R') sum[0]--;
								if (a[i+j][i+k] == 'G') sum[1]--;
								if (a[i+j][i+k] == 'B') sum[2]--;
								a[i+j][i+k] = clipboard[j][k];																
							}
				}
				for (int i = 0;i < 3;i++)
				ans.push_back(sum[i]);
				return ans;
			}
			else{
				int c[3];
				for (int i = 0;i < min(w,h);i++){
					memset(c,0,sizeof(c));
					for (int j = 0;j < w;j++)
						for (int k = 0;k < h;k++)
							if (clipboard[j][k] != '.'){
								if (clipboard[j][k] == 'R') sum[0]++,c[0]++;
								if (clipboard[j][k] == 'G') sum[1]++,c[1]++;
								if (clipboard[j][k] == 'B') sum[2]++,c[2]++;
								if (a[i+j][i+k] == 'R') sum[0]--,c[0]--;
								if (a[i+j][i+k] == 'G') sum[1]--,c[1]--;
								if (a[i+j][i+k] == 'B') sum[2]--,c[2]--;
								a[i+j][i+k] = clipboard[j][k];																
							}
				}
				for (int i = 0;i < 3;i++)
					sum[i] += ((ll)T-min(w,h))*c[i];
				
				for (int i = 0;i < 3;i++)
					ans.push_back(sum[i]);
				return ans;				
			}
		}
};
