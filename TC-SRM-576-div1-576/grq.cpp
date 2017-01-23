#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=305,mod=1e9+9;
int n,a[N],sum[N],dp[N][N][3];

vi make(vector<string> a){
	string s="";
	int now=0;
	vi res;res.clear();
	for(int i=0;i<a.size();i++) s+=a[i];
	for(int i=0;i<s.length();i++)
		res.pb(s[i]-'0');
	return res;
}
void ch(int &x,int y){
	x+=y;if(x>=mod) x-=mod;
}

class TheExperiment{
public:
	int countPlacements(vector<string> water, int M, int L, int A, int B){
		vi tmp=make(water);n=tmp.size();
		for(int i=1;i<=n;i++) a[i]=tmp[i-1];
		sum[0]=0;for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
		memset(dp,0,sizeof(dp));
		dp[0][0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=M;j++){
				dp[i][j][0]=(dp[i-1][j][2]+dp[i-1][j][0])%mod;
				if(!j) continue;
				for(int k=max(0,i-L);k<i;k++){
					if(sum[i]-sum[k]>B||sum[i]-sum[k]<A) continue;
					ch(dp[i][j][2],dp[k][j-1][2]);
					if(i-k==L) ch(dp[i][j][2],(dp[k][j-1][1]+dp[k][j-1][0])%mod);
					else ch(dp[i][j][1],(dp[k][j-1][1]+dp[k][j-1][0])%mod);
				}
			}
		}
		return (dp[n][M][0]+dp[n][M][2])%mod;
	}
};
