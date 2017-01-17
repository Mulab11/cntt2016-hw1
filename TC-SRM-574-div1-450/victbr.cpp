#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int M = 262144+10,A = 20;

class PolygonTraversal{
	public:
		int pre[A],n,m;
		ll f[M][A],ans;
		long long count(int N, vector <int> points){
			n = N;m = points.size();
			int u = 0;
			for (int i = 0;i < m;i++)
				u |= 1 << points[i] >> 1;
			f[u][points[m-1]] = 1;
			
			for (int i = u;i < (1<<n);i++)
				for (int k = 1;k <= n;k++){
					if (!(i&u)) continue;				
					if (f[i][k] == 0) continue;
//					printf("%d %d\n",i,k);
					for (int j = 0;j < n;j++)
						if (i&(1<<j)) pre[j+1] = 1;else pre[j+1] = 0;
					for (int j = 1;j <= n;j++) pre[j] += pre[j-1];
					for (int j = 1;j <= n;j++)
						if (!(i&(1<<j>>1))){
							bool flag1 = 0,flag2 = 0;
							if (j < k){
								flag1 = (pre[k-1]-pre[j] > 0);
								flag2 = (pre[n]-pre[k] + pre[j-1] > 0);
							}
							else{
								flag1 = (pre[j-1]-pre[k] > 0);
								flag2 = (pre[n]-pre[j] + pre[k-1] > 0);						
							}
							if (flag1&flag2){
								f[i|(1<<j>>1)][j] += f[i][k];
							}
						}
			}
			for (int i = 1;i <= n;i++)
				if (abs(points[0]-i) > 1 && i%n+1 != points[0] && points[0]%n+1 != i)//头尾相临不合法 
					ans += f[(1<<n)-1][i];
			return ans;
		}
}X;




