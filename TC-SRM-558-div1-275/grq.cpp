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

const int R=0,G=1,B=2,N=55,inf=1e6;

bool can[N][N][3];
int dp[N][3],n,sc,pc;
string s;

class Stamp{
public:
	int getMinimumCost(string desiredColor, int stampCost, int pushCost){
		s=desiredColor;
		sc=stampCost,pc=pushCost;
		n=s.length();
		s=' '+s;
//		debug(s);
		for(int i=1;i<=n;i++){
			can[i][i-1][R]=can[i][i-1][G]=can[i][i-1][B]=1;
			for(int j=i;j<=n;j++){
				for(int k=0;k<3;k++) can[i][j][k]=can[i][j-1][k];
				if(s[j]=='*') continue;
				if(s[j]!='R') can[i][j][R]=0;
				if(s[j]!='G') can[i][j][G]=0;
				if(s[j]!='B') can[i][j][B]=0;
			}
		}
//		debug(can[1][5][R]);
		int ans=1e9+7;
		for(int L=1;L<=n;L++){
			for(int j=0;j<=n;j++)
				for(int k=0;k<3;k++) dp[j][k]=inf;
			for(int j=0;j<3;j++) if(can[1][L][j]) dp[L][j]=1;
			for(int j=L+1;j<=n;j++)
				for(int k=0;k<3;k++){
					if(can[j-L+1][j][k])
						for(int t=0;t<3;t++)
							dp[j][k]=min(dp[j][k],dp[j-L][t]+1);
					for(int t=j-L+1;t<j;t++) 
						if(can[t+1][j][k]) dp[j][k]=min(dp[j][k],dp[t][k]+1);
				}
			int res=inf;
			for(int k=0;k<3;k++)
				res=min(res,dp[n][k]);
			if(res<inf) ans=min(ans,res*pc+L*sc);
		}
		return ans;
	}
};
