#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int inf=1000000000;

int n,m,R,C,dp[3000010],a[15],pow3[15];
pii b[15];
bool s1[15],s2[15];

//the program may look prettier if we assume the game has n rounds,not only numGuesses rounds
int dfs(int k1,int s,int p)
{
	if (dp[k1]!=-1) return dp[k1];
	dp[k1]=-2;
	bool v=0;
	for (int i=0;i<n;i++)
		if (k1/pow3[i]%3==0)
		{
			v=1;
			int t=inf;
			if (p<m) t=dfs(k1+pow3[i]*2,s-1,p+1);
			if (t==-2) t=inf; else t+=a[p]*(s>0);
			int w=dfs(k1+pow3[i],s-1,p);
			if (w!=-2) t=min(t,w);
			if (t!=inf) dp[k1]=max(dp[k1],t);
		}
	if (!v)
	{
		dp[k1]=0;
		if (p<m) dp[k1]=-2;//illegal
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		for (int i=0;i<n;i++) if (k1/pow3[i]%3==1) {s1[b[i].x]^=1;s2[b[i].y]^=1;}
		for (int i=0;i<R;i++) if (s1[i]) dp[k1]=-2;
		for (int i=0;i<C;i++) if (s2[i]) dp[k1]=-2;
	}
	return dp[k1];
}

struct MagicalHats 
{
    int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses)
    {
    	R=board.size();C=board[0].size();
    	n=0;
    	for (int i=0;i<R;i++)
    		for (int j=0;j<C;j++)
    			if (board[i][j]=='H')
    				b[n++]=mp(i,j);
    	pow3[0]=1;for (int i=1;i<=n;i++) pow3[i]=pow3[i-1]*3;
    	m=coins.size();
    	for (int i=0;i<m;i++) a[i]=coins[i];
    	sort(a,a+m);//it's optimal for the magician to arrange the coins in non-decreasing order
    	memset(dp,-1,sizeof(dp));
    	return max(dfs(0,numGuesses,0),-1);
    }
};
