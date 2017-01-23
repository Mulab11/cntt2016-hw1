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

const int mod=1e9+7;
int n;
ll dp[2][2505][2][2][4];
string s;

class LittleElephantAndRGB{
public:
	long long getNumber(vector <string> list, int minGreen){
		s=" ";
		for(int i=0;i<list.size();i++) s=s+list[i];
		n=s.length()-1;
		int d=0;
		memset(dp,0,sizeof(dp));
		dp[0][0][0][0][0]=1;
		for(int i=1;i<=n;i++){
			d^=1;
			memset(dp[d],0,sizeof(dp[d]));
			int g=(s[i]=='G');
			for(int j=0;j<=n;j++)
				for(int a=0;a<2;a++){
					bool t=a|(j+g>=minGreen);
					for(int k=0;k<=2;k++){
					dp[d][(j+g)*g][t][1][k]+=dp[d^1][j][a][1][k];
					dp[d][(j+g)*g][t][1][k+1]+=dp[d^1][j][a][1][k];
					dp[d][(j+g)*g][t][1][k+1]+=dp[d^1][j][a][0][k];

					dp[d][j][a][0][k]+=dp[d^1][j][a][1][k];
					dp[d][j][a][0][k]+=dp[d^1][j][a][0][k];
					}
				}
		}
		ll ans=0;
		for(int j=0;j<=n;j++)
			ans+=dp[d][j][1][0][2]+dp[d][j][1][1][2];
		return ans;
	}
};
