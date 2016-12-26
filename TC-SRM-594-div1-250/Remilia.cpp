#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
using namespace std;
const int maxn=55;
int f[maxn][maxn];

/*

转个比例然后DP一下啊。。？
*/

class AstronomicalRecords{
public:
	int minimalPlanets(vector<int>a,vector<int>b){
		int n=a.size(),m=b.size(),ans=0;
		rep(i,0,n-1) rep(j,0,m-1){
			int mula=b[j],mulb=a[i];
			memset(f,0,sizeof f);
			rep(i,1,n) rep(j,1,m){
				if ((ll)a[i-1]*mula==(ll)b[j-1]*mulb) f[i][j]=max(f[i][j],f[i-1][j-1]+1);
				f[i][j]=max(f[i][j],f[i-1][j]);
				f[i][j]=max(f[i][j],f[i][j-1]);
			}
			ans=max(ans,f[n][m]);
		}
		return n+m-ans;
	}
};
