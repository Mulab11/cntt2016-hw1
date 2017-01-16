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

int n,R,C;
int a[64][2],dp[16][16][16][16];

int solve(int x1,int x2,int y1,int y2)
{
	if (dp[x1][x2][y1][y2]!=-1) return dp[x1][x2][y1][y2];
	dp[x1][x2][y1][y2]=n*(R+C);
	for (int i=0;i<n;i++)
		if (!(x1<=a[i][0]&&a[i][0]<=x2&&y1<=a[i][1]&&a[i][1]<=y2))
		{
			int x3=min(x1,a[i][0]),x4=max(x2,a[i][0]);
			int y3=min(y1,a[i][1]),y4=max(y2,a[i][1]);
			int t=solve(x3,x4,y3,y4)+max(max(abs(x1-a[i][0]),abs(x2-a[i][0])),max(abs(y1-a[i][1]),abs(y2-a[i][1])));
			for (int j=0;j<n;j++)
				if (i!=j&&(!(x1<=a[j][0]&&a[j][0]<=x2&&y1<=a[j][1]&&a[j][1]<=y2))&&(x3<=a[j][0]&&a[j][0]<=x4&&y3<=a[j][1]&&a[j][1]<=y4))
					t+=max(max(abs(x3-a[j][0]),abs(x4-a[j][0])),max(abs(y3-a[j][1]),abs(y4-a[j][1])));
			dp[x1][x2][y1][y2]=min(dp[x1][x2][y1][y2],t);
		}
	if (dp[x1][x2][y1][y2]==n*(R+C)) dp[x1][x2][y1][y2]=0;
	return dp[x1][x2][y1][y2];
}

struct EllysChessboard 
{
    int minCost(vector <string> board)
    {
    	R=board.size();C=board[0].size();
    	n=0;
    	for (int i=0;i<R;i++)
    		for (int j=0;j<C;j++)
    			if (board[i][j]=='#')
    			{
    				a[n][0]=i+j;a[n++][1]=i-j+C-1;
    			}
    	int ans=(R+C)*n;
    	memset(dp,-1,sizeof(dp));
    	for (int i=0;i<n;i++) ans=min(ans,solve(a[i][0],a[i][0],a[i][1],a[i][1]));
    	return ans;
	}
};
