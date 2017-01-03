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

int n;
string dp[55][55][3][3],t,ans;
char a[55],b[55];

string solve(int l,int r,int x,int y)
{
	if (l>r)
	{
		if (x==0||(x==1&&y==0)) return " "; else return "";
	}
	if (dp[l][r][x][y]!="") return dp[l][r][x][y];
	dp[l][r][x][y]=" ";//there is no legal string
	int k=r-l;
	int tx=x;
	if (tx==1&&a[k]<b[l]) tx=0;
	if (tx==1&&a[k]>b[l]) tx=2;
	t=solve(l+1,r,tx,y);
	if (t!=" ") dp[l][r][x][y]=a[k]+t;
	int ty=y;
	if (a[k]<b[r]) ty=0;
	if (a[k]>b[r]) ty=2;
	t=solve(l,r-1,x,ty);
	if (t!=" ")
	{
		t+=a[k];
		if (dp[l][r][x][y]==" "||t<dp[l][r][x][y]) dp[l][r][x][y]=t;
	}
	return dp[l][r][x][y];
}

struct LeftRightDigitsGame2 
{
    string minNumber(string digits, string lowerBound)
    {
    	n=digits.size();
    	for (int i=0;i<n;i++) a[i]=digits[i];
    	for (int i=0;i<n;i++) b[i]=lowerBound[i];
    	ans=solve(0,n-1,1,1);
    	for (int i=0;i<n;i++)
    		for (int j=0;j<n;j++)
    			for (int x=0;x<3;x++)
    				for (int y=0;y<3;y++)
    					dp[i][j][x][y]="";
    	if (ans==" ") return ""; else return ans;
    }
};
