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

const int N=55,inf=1e9;
int dp[N][2][2][2];

class BallsSeparating{
public:
	int minOperations(vector<int> red, vector<int> green, vector<int> blue){
		int n=red.size();
		for(int a=0;a<2;a++)
			for(int b=0;b<2;b++)
				for(int c=0;c<2;c++)
					dp[0][a][b][c]=inf;
		dp[0][0][0][0]=0;
		for(int i=1;i<=n;i++){
			
		for(int a=0;a<2;a++)
			for(int b=0;b<2;b++)
				for(int c=0;c<2;c++)
					dp[i][a][b][c]=inf;
			for(int a=0;a<2;a++)
				for(int b=0;b<2;b++)
					for(int c=0;c<2;c++){
						dp[i][1][b][c]=min(dp[i][1][b][c],dp[i-1][a][b][c]+green[i-1]+blue[i-1]);
						dp[i][a][1][c]=min(dp[i][a][1][c],dp[i-1][a][b][c]+red[i-1]+blue[i-1]);
						dp[i][a][b][1]=min(dp[i][a][b][1],dp[i-1][a][b][c]+green[i-1]+red[i-1]);
					}
		}
		return dp[n][1][1][1]<inf?dp[n][1][1][1]:-1;
	}
};
