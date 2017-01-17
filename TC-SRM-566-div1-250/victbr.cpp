#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60;

class PenguinSledding{
	public:
		int m,degree[N],n;
		bool a[N][N];
		long long ans;
		long long countDesigns(int numCheckpoints, vector <int> checkpoint1, vector <int> checkpoint2){
			m = checkpoint1.size();ans = 0;n = numCheckpoints;
			for (int i = 0;i < m;i++){
				degree[checkpoint1[i]]++;
				degree[checkpoint2[i]]++;
				a[checkpoint1[i]][checkpoint2[i]] = 1;
				a[checkpoint2[i]][checkpoint1[i]] = 1;				
			}
			ans -= m;
			for (int i = 1;i <= n;i++)
				ans += ((ll)1<<degree[i]) - 1;
			for (int i = 1;i <= n;i++)
				for (int j = i+1;j <= n;j++)
					for (int k = j+1;k <= n;k++)
						if (a[i][j] && a[j][k] && a[i][k]) ans++;
			return ans+1;
		}
};
