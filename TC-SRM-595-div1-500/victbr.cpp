#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2500+10;

class LittleElephantAndRGB{
	public:
		ll f[N],g[N][N],h[N];
		int n;
		string s;
		long long getNumber(vector <string> list, int minGreen){
			s = ' ';
			for (int i = 0;i < list.size();i++)
				s = s + list[i];
			n = s.size();
			f[0] = 0;
			g[0][0] = 1;
			for (int i = 1;i <= n;i++){
				if (s[i] == 'G'){
					for (int j = i;j >= 0;j--)
						h[j+1] = h[j];
					h[1]++;
				}
				else{
					for (int j = 1;j <= i;j++)
						if (j < m){
							h[0] += h[j];
							h[j] = 0;
						}
					h[0]++;
				}
				for (int j = 0;j <= i;j++)
					g[i][j] = g[i-1][j]+h[j];
			}	
			
		}
};
