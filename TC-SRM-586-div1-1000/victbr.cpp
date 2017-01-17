#include<bits/stdc++.h>
using namespace std;

const int N = 60;

class StringWeight{
	public:
		int f[N][N][N],n,ans;
		int getMinimum(vector<int> L)
		{
			ans = 0x7fffffff;
			n = L.size();
			memset(f,0x3f,sizeof(f));
			f[0][0][0]=0;
			for (int i = 0;i < n;i++){
				int use = min(26,L[i]);
				for (int j = 0;j <= 26;j++)
					for (int k = 0;j+k <= 26 && use <= 26-k ;k++){
						int c = max(0,use-j);
						for (int a = 0;a <= j;a++)
							for (int b = 0;b <= c;b++)
								f[i+1][a+b][j-a+c-b+k] = min(f[i+1][a+b][j-a+c-b+k],f[i][j][k]+(j-a)*(j-a+1)/2+b*(b-1)/2+a*L[i]+max(0,L[i]-26)*(a==0));
							
					}
			}
			for (int i = 0;i <= 26;i++)
				ans = min(ans,f[n][0][i]);
			return ans;
		}
};
