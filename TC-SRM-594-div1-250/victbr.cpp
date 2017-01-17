#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60;

class AstronomicalRecords{
	public:
		int n,m,f[N][N],ans;
		ll a[N],b[N];
		int minimalPlanets(vector <int> A, vector <int> B){
			n = A.size();m = B.size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++){
					
					for (int k = 0;k < n;k++)
						a[k+1] = (ll)A[k]*B[j];
					for (int k = 0;k < m;k++)
						b[k+1] = (ll)B[k]*A[i];
					memset(f,0,sizeof(f));
					for (int k = 1;k <= n;k++)
						for (int l = 1;l <= m;l++){
							f[k][l] = max(f[k][l-1],f[k-1][l]);
							if (a[k] == b[l]) f[k][l] = max(f[k][l],f[k-1][l-1]+1);
						}
					ans = max(ans,f[n][m]);
				}
			return n+m-ans;
		}
};
