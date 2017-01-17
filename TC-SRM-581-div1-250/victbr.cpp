#include <bits/stdc++.h>

using namespace std;

const int N = 60;

class SurveillanceSystem{
	public:
		string ans;
		int n,m,a[N],b[N],c[N],f[N][N];
		string getContainerInfo(string containers, vector <int> reports, int L){
			n = reports.size();m = containers.size();
			for (int i = 0;i < n;i++) a[reports[i]]++;
			int l = 0,r =1;
			for (r = 0;r < L;r++) b[0] += (containers[r] == 'X');
			c[b[0]]++;
			l = 1;
			while (l + L <= m){
				b[l] = b[l-1];
				b[l] -= (containers[l-1] == 'X');
				b[l] += (containers[r] == 'X');
				r++;
				c[b[l]]++;
				l++;
			}
			for (int i = 0;i + L <= m;i++)
				for (int j = 0;j < L;j++)
					f[i+j][b[i]]++;
			for (int i = 0;i < m;i++){
				bool flag1 = 0,flag2 = 0;
				for (int j = 0;j < m;j++){
					if (f[i][j] > 0) flag1 = 1;
					if (c[j]-f[i][j] < a[j]) flag2 = 1;
				}
				if (flag2) ans = ans + '+';
				else if (flag1) ans = ans + '?';
				else ans = ans + '-';
			}
			return ans;
		}
};

	
