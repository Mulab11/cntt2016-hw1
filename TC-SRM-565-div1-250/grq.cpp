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

const int N=55;
const ll inf=1ll<<60;
int n;
ll dp[2][N<<2];

class MonstersValley{
public:
	int minimumPrice(vector<long long> dread, vector <int> price){
		n=price.size();
		int k=0;
		memset(dp,0,sizeof(dp));
		for(int i=0;i<n;i++){
			k^=1;for(int j=0;j<=n*2;j++) dp[k][j]=-inf;
			int t=-1;
			for(int j=0;j<=n*2;j++)
				if(dp[k^1][j]>=dread[i]){t=j;break;}
				
			if(t==-1){
				for(int j=price[i];j<=n*2;j++) dp[k][j]=dp[k^1][j-price[i]]+dread[i];
			}
			else{
				for(int j=price[i];j<=n*2;j++) dp[k][j]=dp[k^1][j-price[i]]+dread[i];
				for(int j=t;j<=n*2;j++) dp[k][j]=max(dp[k][j],dp[k^1][j]);
			}
		}
		for(int j=0;j<=n*2;j++) if(dp[k][j]>=0) return j;
		return -1;
	}
};
